#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 7;
const int maxx = 1e6 + 7;
const int logn = 19;

struct ft {
    int n;
    vector <int> t;

    ft (int n) {
        this->n = n;
        t.resize(n);
    }

    void inc(int k, int x) {
        for (; k < n; k += k & -k) t[k] += x;
    }

    int get(int r) {
        int ans = 0;
        for (; r > 0; r -= r & -r) ans += t[r];
        return ans;
    }

    int get(int l, int r) {
        return get(r) - get(l - 1);
    }
};

ft tree(maxx);

int t = 0;
vector <vector <pair <int, int>>> g(maxn), qadd(maxn), qrem(maxn);
vector <vector <int>> up(logn, vector <int> (maxn));
vector <int> ans(maxn), tin(maxn), tout(maxn);

bool is_anc(int v, int u) {
    return tin[v] <= tin[u] && tout[u] <= tout[v];
}

int lca(int v, int u) {
    for (int l = logn - 1; l >= 0; l--) {
        if (!is_anc(up[l][v], u)) v = up[l][v];
    }
    return up[0][v];
}

void get_time(int v, int p = -1) {
    tin[v] = t++;
    up[0][v] = (p == -1 ? 0 : p);
    for (int l = 1; l < logn; l++) up[l][v] = up[l - 1][up[l - 1][v]];
    for (auto [u, len] : g[v]) {
        if (u != p) get_time(u, v);
    }
    tout[v] = t++;
}

void dfs(int v, int p = -1) {
    for (auto u : qadd[v]) ans[u.first] += tree.get(u.second);
    for (auto u : qrem[v]) ans[u.first] -= tree.get(u.second);
    for (auto [u, len] : g[v]) {
        if (u != p) {
            tree.inc(len, 1);
            dfs(u, v);
            tree.inc(len, -1);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, q; cin >> n >> q;
    for (int i = 0, v, u, c; i < n - 1; i++) {
        cin >> v >> u >> c; v--, u--;
        g[v].push_back({u, c});
        g[u].push_back({v, c});
    }
    get_time(0);
    for (int i = 0, v, u, x; i < q; i++) {
        cin >> v >> u >> x; v--, u--;
        if (is_anc(u, v)) swap(u, v);
        if (is_anc(v, u)) {
            qadd[u].push_back({i, x});
            qrem[v].push_back({i, x});
        } else {
            int anc = lca(v, u);
            qadd[v].push_back({i, x});
            qadd[u].push_back({i, x});
            qrem[anc].push_back({i, x});
            qrem[anc].push_back({i, x});
        }
    }
    dfs(0);
    for (int i = 0; i < q; i++) cout << ans[i] << '\n';
    return 0;
}