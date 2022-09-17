#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 7;
const int inf = 1e9 + 179;

struct maxtree {
    struct node {
        int max, promise;
    };
    int size;
    vector <node> t;

    maxtree(int n) {
        size = 1;
        while (size < n) size <<= 1;
        t.resize(2 * size - 1, {0, 0});
    }

    void push(int id, int lb, int rb) {
        if (t[id].promise != 0) {
            t[id].max += t[id].promise;
            if (lb + 1 < rb) {
                t[id * 2 + 1].promise += t[id].promise;
                t[id * 2 + 2].promise += t[id].promise;
            }
            t[id].promise = 0;
        }
    }

    void update(int l, int r, int x, int id, int lb, int rb) {
        push(id, lb, rb);
        if (lb >= r || rb <= l) return;
        if (l <= lb && rb <= r) {
            t[id].promise += x;
            push(id, lb, rb);
            return;
        }
        int m = (lb + rb) / 2;
        update(l, r, x, id * 2 + 1, lb, m);
        update(l, r, x, id * 2 + 2, m, rb);
        t[id].max = max(t[id * 2 + 1].max, t[id * 2 + 2].max);
    }

    void update(int l, int r, int x) {
        update(l, r, x, 0, 0, size);
    }

    int get(int l, int r, int id, int lb, int rb) {
        push(id, lb, rb);
        if (lb >= r || rb <= l) return INT_MIN;
        if (l <= lb && rb <= r) return t[id].max;
        int m = (lb + rb) / 2;
        return max(get(l, r, id * 2 + 1, lb, m), get(l, r, id * 2 + 2, m, rb));
    }
    
    int get(int l, int r) {
        return get(l, r, 0, 0, size);
    }
};

struct mintree {
    struct node {
        int min, promise;
    };
    int size;
    vector <node> t;

    mintree(int n) {
        size = 1;
        while (size < n) size <<= 1;
        t.resize(2 * size - 1, {0, 0});
    }

    void push(int id, int lb, int rb) {
        if (t[id].promise != 0) {
            t[id].min += t[id].promise;
            if (lb + 1 < rb) {
                t[id * 2 + 1].promise += t[id].promise;
                t[id * 2 + 2].promise += t[id].promise;
            }
            t[id].promise = 0;
        }
    }

    void update(int l, int r, int x, int id, int lb, int rb) {
        push(id, lb, rb);
        if (lb >= r || rb <= l) return;
        if (l <= lb && rb <= r) {
            t[id].promise += x;
            push(id, lb, rb);
            return;
        }
        int m = (lb + rb) / 2;
        update(l, r, x, id * 2 + 1, lb, m);
        update(l, r, x, id * 2 + 2, m, rb);
        t[id].min = min(t[id * 2 + 1].min, t[id * 2 + 2].min);
    }

    void update(int l, int r, int x) {
        update(l, r, x, 0, 0, size);
    }

    int get(int l, int r, int id, int lb, int rb) {
        push(id, lb, rb);
        if (lb >= r || rb <= l) return INT_MAX;
        if (l <= lb && rb <= r) return t[id].min;
        int m = (lb + rb) / 2;
        return min(get(l, r, id * 2 + 1, lb, m), get(l, r, id * 2 + 2, m, rb));
    }
    
    int get(int l, int r) {
        return get(l, r, 0, 0, size);
    }
};

int counter = 0;
vector <vector <int>> g(maxn);
vector <pair <int, int>> lr(maxn), borders(maxn, {INT_MAX, INT_MIN});
vector <int> ans(maxn);

maxtree mxtree(maxn);
mintree mntree(maxn);

void dfs(int v, int p) {
    bool any = 0;
    for (auto u : g[v]) {
        if (u != p) {
            any = 1;
            dfs(u, v);
            borders[v].first = min(borders[v].first, borders[u].first);
            borders[v].second = max(borders[v].second, borders[u].second);
        }
    }
    if (!any) {
        borders[v] = {counter, counter};
        counter++;
    }
    mxtree.update(borders[v].first, borders[v].second + 1, lr[v].first);
    mntree.update(borders[v].first, borders[v].second + 1, lr[v].second);
}

void get_ans(int v, int p) {
    if (g[v].size() == 1 && borders[v].first == borders[v].second) {
        mxtree.update(borders[v].first, borders[v].second + 1, -inf);
        mntree.update(borders[v].first, borders[v].second + 1, inf);
    }
    ans[v] = (mxtree.get(0, counter) <= mntree.get(0, counter));
    if (g[v].size() == 1 && borders[v].first == borders[v].second) {
        mxtree.update(borders[v].first, borders[v].second + 1, inf);
        mntree.update(borders[v].first, borders[v].second + 1, -inf);
    }
    for (auto u : g[v]) {
        if (u != p) {
            mxtree.update(borders[u].first, borders[u].second + 1, -lr[v].first);
            mntree.update(borders[u].first, borders[u].second + 1, -lr[v].second);
            if (borders[v].first < borders[u].first) {
                mxtree.update(borders[v].first, borders[u].first, lr[u].first);
                mntree.update(borders[v].first, borders[u].first, lr[u].second);
            }
            if (borders[u].second < counter) {
                mxtree.update(borders[u].second + 1, counter, lr[u].first);
                mntree.update(borders[u].second + 1, counter, lr[u].second);
            }
            get_ans(u, v);
            mxtree.update(borders[u].first, borders[u].second + 1, lr[v].first);
            mntree.update(borders[u].first, borders[u].second + 1, lr[v].second);
            if (borders[v].first < borders[u].first) {
                mxtree.update(borders[v].first, borders[u].first, -lr[u].first);
                mntree.update(borders[v].first, borders[u].first, -lr[u].second);
            }
            if (borders[u].second < counter) {
                mxtree.update(borders[u].second + 1, counter, -lr[u].first);
                mntree.update(borders[u].second + 1, counter, -lr[u].second);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    for (int i = 0, v, u; i < n - 1; i++) {
        cin >> v >> u; v--, u--;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    for (int i = 0; i < n; i++) cin >> lr[i].first >> lr[i].second;
    if (n == 2) {
        cout << 1 << ' ' << 1;
        return 0;
    }
    int s = 0;
    for (int i = 0; i < n; i++) {
        if (g[i].size() > 1) s = i;
    }
    dfs(s, -1);
    get_ans(s, -1);
    for (int i = 0; i < n; i++) cout << ans[i] << ' ';
    return 0;
}