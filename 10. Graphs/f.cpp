#include <bits/stdc++.h>
using namespace std;

vector <vector <int>> g1, g2;
vector <vector <pair <int, int>>> g3;
vector <int> order, used, comp, comp_size, h, d, is_ts, ans, petl, a1, a2;

void topsort(int v) {
    used[v] = 1;
    for (int u : g1[v]) {
        if (!used[u]) topsort(u);
    }
    order.push_back(v);
}

void color(int v, int c) {
    comp[v] = c;
    comp_size[c]++;
    for (int u : g2[v]) {
        if (comp[u] == -1) color(u, c);
    }
}

void ts(int v, int p = -1) {
    used[v] = 1;
    d[v] = h[v] = (p == -1 ? 0 : h[p] + 1);
    for (auto [u, id] : g3[v]) {
        if (u != p) {
            if (used[u]) d[v] = min(d[v], h[u]);
            else {
                ts(u, v);
                d[v] = min(d[v], d[u]);
                if (d[u] > h[v] && id != -1) is_ts[id] = 1;
            }
        }
    }
}

void achieve(vector <vector <int>>& g, vector <int>& a, int v) {
    a[v] = 1;
    for (int u : g[v]) {
        if (!a[u]) achieve(g, a, u);
    }
}

void dfs(int v) {
    used[v] = 1;
    if (!petl[v] && a1[v] && a1[v] && is_ts[v] && comp_size[comp[v]] == 1) {
        ans.push_back(v);
    }
    for (int u : g1[v]) {
        if (!used[u]) dfs(u);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t; cin >> t;
    while (t--) {
        g1.clear(), g2.clear(), g3.clear(), order.clear(), used.clear(), comp.clear(), comp_size.clear(), h.clear(), d.clear(), is_ts.clear(), ans.clear(), petl.clear(), a1.clear(), a2.clear();
        int n, m; cin >> n >> m;
        g1.resize(n), g2.resize(n), g3.resize(2 * n), used.resize(2 * n, 0), comp.resize(n, -1), h.resize(2 * n, 0), d.resize(2 * n, 0), is_ts.resize(n, 0), petl.resize(n, 0), a1.resize(n, 0), a2.resize(n, 0);
        for (int i = 0, v, u; i < m; i++) {
            cin >> v >> u; v--, u--;
            if (v == u) {
                petl[v] = 1;
                continue;
            }
            g1[v].push_back(u);
            g2[u].push_back(v);
        }
        achieve(g1, a1, 0);
        achieve(g2, a2, n - 1);
        for (int v = 0; v < n; v++) {
            if (!a1[v] || !a2[v]) continue;
            g3[2 * v].push_back({2 * v + 1, v});
            g3[2 * v + 1].push_back({2 * v, v});
            for (int u : g1[v]) {
                if (!a1[u] || !a2[u]) continue;
                g3[2 * v + 1].push_back({2 * u, -1});
                g3[2 * u].push_back({2 * v + 1, -1});
            }
        }
        for (int i = 0; i < n; i++) {
            if (!used[i]) topsort(i);
        }
        reverse(order.begin(), order.end());
        for (int v : order) {
            if (comp[v] == -1) {
                comp_size.push_back(0);
                color(v, (int)comp_size.size() - 1);
            }
        }
        used.assign(2 * n, 0);
        for (int i = 0; i < 2 * n; i++) {
            if (!used[i]) ts(i);
        }
        used.assign(2 * n, 0);
        dfs(0);
        cout << (int)ans.size() << '\n';
        for (int u : ans) cout << u + 1 << ' ';
        cout << '\n';
    }
    return 0;
}