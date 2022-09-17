#include <bits/stdc++.h>
using namespace std;

const int K = 300;
const int MAXN = 1e5 + 7;

int t = 0;
vector <vector <pair <int, int>>> g;
vector <int> tin(MAXN), tout(MAXN), order, wayup(MAXN, -1), waydown(MAXN, -1);

struct q {
    int l, r, index;
};

struct mex {
    int size;
    vector <int> v, count;

    mex(int size) {
        this->size = size;
        v.resize(size);
        count.resize((size - 1) / K + 1);
    }

    void add(int x) {
        if (v[x] == 0) count[x / K]++;
        v[x]++;
    }

    void del(int x) {
        if (v[x] == 0) return;
        if (v[x] == 1) count[x / K]--;
        v[x]--;
    }

    int get() {
        int pos = 0;
        while (count[pos] == K) pos++;
        pos *= K;
        while (v[pos] > 0) pos++;
        return pos;
    }
};

void dfs(int v, int p = -1) {
    tin[v] = t++;
    for (auto u : g[v]) {
        if (u.first != p) {
            if (waydown[v] == -1) waydown[v] = u.second;
            if (wayup[u.first] == -1) wayup[u.first] = u.second; 
            order.push_back(u.second);
            dfs(u.first, v);
            order.push_back(u.second);
        }
    }
    tout[v] = t;
}

bool is_anc(int v, int u) {
    return tin[v] <= tin[u] && tout[v] >= tout[u];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, num; cin >> n >> num;
    g.resize(n);
    vector <int> value(n - 1);
    for (int i = 0, v, u, c; i < n - 1; i++) {
        cin >> v >> u >> c; v--, u--;
        value[i] = c;
        g[v].push_back({u, i});
        g[u].push_back({v, i});
    }
    dfs(0);
    vector <int> fmeet(MAXN), smeet(MAXN), used(MAXN);
    for (int i = 0; i < (int)order.size(); i++) {
        if (used[order[i]]) smeet[order[i]] = i;
        else {
            used[order[i]] = 1;
            fmeet[order[i]] = i;
        }
    }
    vector <q> reqs;
    vector <int> ans(num), vis(MAXN);
    for (int i = 0, a, b; i < num; i++) {
        cin >> a >> b; a--, b--;
        if (a == b) {
            ans[i] = 0;
            continue;
        }
        if (is_anc(a, b)) {
            reqs.push_back({fmeet[waydown[a]], fmeet[wayup[b]], i});
        } else if (is_anc(b, a)) {
            reqs.push_back({fmeet[waydown[b]], fmeet[wayup[a]], i});
        } else {
            if (tin[a] > tin[b]) swap(a, b);
            reqs.push_back({smeet[wayup[a]], fmeet[wayup[b]], i});
        }
    }
    sort(reqs.begin(), reqs.end(), [](q& a, q& b){return a.l / K == b.l / K ? (a.l / K % 2 == 0 ? a.r < b.r : a.r > b.r) : a.l / K < b.l / K;});
    int l = 0, r = -1;
    mex inc(n + 1);
    for (auto req : reqs) {
        int tl = req.l, tr = req.r;
        while (r > tr) {
            if (value[order[r]] < n) {
                if (vis[order[r]]) inc.del(value[order[r]]);
                else inc.add(value[order[r]]);
            }
            vis[order[r]] ^= 1;
            r--;
        }
        while (r < tr) {
            ++r;
            if (value[order[r]] < n) {
                if (vis[order[r]]) inc.del(value[order[r]]);
                else inc.add(value[order[r]]);
            }
            vis[order[r]] ^= 1;
        }
        while (l > tl) {
            --l;
            if (value[order[l]] < n) {
                if (vis[order[l]]) inc.del(value[order[l]]);
                else inc.add(value[order[l]]);
            }
            vis[order[l]] ^= 1;
        }
        while (l < tl) {
            if (value[order[l]] < n) {
                if (vis[order[l]]) inc.del(value[order[l]]);
                else inc.add(value[order[l]]);
            }
            vis[order[l]] ^= 1;
            l++;
        }
        ans[req.index] = inc.get();
    }
    for (int u : ans) cout << u << '\n';
    return 0;
}