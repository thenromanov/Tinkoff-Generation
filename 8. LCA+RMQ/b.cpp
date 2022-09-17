#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 7;

int t1 = 0;
vector <vector <int>> g1(maxn), g2(maxn);
vector <int> tin(maxn), tout(maxn), pos(maxn), sz(maxn, 1), order;

struct tree {
    int size;
    vector <vector <int>> t;

    tree(int n) {
        size = 1;
        while (size < n) size <<= 1;
        t.resize(2 * size - 1);
    }

    void build(vector <int>& a, int id, int lb, int rb) {
        if (lb + 1 == rb) {
            if (lb < (int)a.size()) t[id].push_back(a[lb]);
            return;
        }
        int m = (lb + rb) / 2;
        build(a, id * 2 + 1, lb, m);
        build(a, id * 2 + 2, m, rb);
        t[id].resize((int)t[id * 2 + 1].size() + (int)t[id * 2 + 2].size());
        merge(t[id * 2 + 1].begin(), t[id * 2 + 1].end(), t[id * 2 + 2].begin(), t[id * 2 + 2].end(), t[id].begin());
    }
    
    void build(vector <int>& a) {
        build(a, 0, 0, size);
    }

    int get(int l, int r, int lq, int rq, int id, int lb, int rb) {
        if (l >= rb || r <= lb) return 0;
        if (l <= lb && rb <= r) {
            int cntless = lower_bound(t[id].begin(), t[id].end(), lq) - t[id].begin();
            int cntgt = upper_bound(t[id].begin(), t[id].end(), rq) - t[id].begin();
            return cntgt - cntless;
        }
        int m = (lb + rb) / 2;
        return get(l, r, lq, rq, id * 2 + 1, lb, m) + get(l, r, lq, rq, id * 2 + 2, m, rb);
    }

    int get(int l, int r, int lq, int rq) {
        return get(l, r, lq, rq, 0, 0, size);
    }
};

void make1(int v, int p = -1) {
    tin[v] = t1++;
    for (int u : g1[v]) {
        if (u != p) make1(u, v);
    }
    tout[v] = t1++;
}

void make2(int v, int p = -1) {
    pos[v] = (int)order.size();
    order.push_back(tin[v]);
    for (int u : g2[v]) {
        if (u != p) {
            make2(u, v);
            sz[v] += sz[u];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    int s1 = 0, s2 = 0;
    for (int i = 0, c; i < n; i++) {
        cin >> c;
        if (c == 0) {
            s1 = i;
            continue;
        }
        g1[c - 1].push_back(i);
    }
    for (int i = 0, c; i < n; i++) {
        cin >> c;
        if (c == 0) {
            s2 = i;
            continue;
        }
        g2[c - 1].push_back(i);
    }
    make1(s1);
    make2(s2);
    tree mstree(n);
    mstree.build(order);
    int64_t ans = 0;
    for (int i = 0; i < n; i++) ans += mstree.get(pos[i] + 1, pos[i] + sz[i], tin[i], tout[i]);
    cout << ans;
    return 0;
}