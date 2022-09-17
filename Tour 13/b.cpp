#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 7;
const int logn = 17;

struct dsu {
    vector <int> p, sz;

    dsu(int n) {
        p.resize(n), sz.resize(n, 1);
        iota(p.begin(), p.end(), 0);
    }

    int find(int v) {
        if (v == p[v]) return v;
        return p[v] = find(p[v]);
    }

    void unite(int v, int u) {
        v = find(v), u = find(u);
        if (sz[v] > sz[u]) swap(v, u);
        sz[u] += sz[v];
        p[v] = u;
    }
};

int t = 0;
vector <vector <pair <int, int>>> g(maxn);
vector <vector <int>> up(logn, vector <int> (maxn)), mx(logn, vector <int> (maxn, INT_MIN));
vector <int> tin(maxn, -1), tout(maxn); 

bool is_anc(int v, int u) {
    return tin[v] <= tin[u] && tout[u] <= tout[v];
}

void dfs(int v, int p = -1, int c = INT_MIN) {
    tin[v] = t++;
    up[0][v] = (p == -1 ? 0 : p);
    mx[0][v] = c;
    for (int l = 1; l < logn; l++) {
        up[l][v] = up[l - 1][up[l - 1][v]];
        mx[l][v] = max(mx[l - 1][v], mx[l - 1][up[l - 1][v]]);
    }
    for (auto [u, l] : g[v]) {
        if (u != p) dfs(u, v, l);
    }
    tout[v] = t++;
}

int get(int v, int u) {
    int vv = v, uu = u, ans = INT_MIN;
    for (int l = logn - 1; l >= 0; l--) {
        if (!is_anc(v, u) && !is_anc(up[l][vv], u)) {
            ans = max(ans, mx[l][vv]);
            vv = up[l][vv];
        }
        if (!is_anc(u, v) && !is_anc(up[l][uu], v)) {
            ans = max(ans, mx[l][uu]);
            uu = up[l][uu];
        }
    }
    if (!is_anc(v, u)) ans = max(ans, mx[0][vv]);
    if (!is_anc(u, v)) ans = max(ans, mx[0][uu]);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m; cin >> n >> m;
    vector <pair <int, pair <int, int>>> e(m);
    for (int i = 0; i < m; i++) cin >> e[i].second.first >> e[i].second.second >> e[i].first;
    sort(e.rbegin(), e.rend());
    vector <pair <int, pair <int, int>>> to_check;
    dsu cnm(n);
    for (auto y : e) {
        auto [l, vu] = y;
        if (cnm.find(vu.first - 1) == cnm.find(vu.second - 1)) to_check.push_back(y);
        else {
            g[vu.first - 1].push_back({vu.second - 1, l});
            g[vu.second - 1].push_back({vu.first - 1, l});
            cnm.unite(vu.first - 1, vu.second - 1);
        }
    }
    for (int i = 0; i < n; i++) {
        if (tin[i] == -1) dfs(i);
    }
    int ans = 0;
    for (auto u : to_check) ans = max(ans, u.first + get(u.second.first - 1, u.second.second - 1));
    cout << ans << '\n';
    return 0;
}