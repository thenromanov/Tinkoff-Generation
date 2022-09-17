#include <bits/stdc++.h>
using namespace std;

vector <vector <pair <int, int>>> g;
vector <int> used, used_edge, h, d, is_bridge;

void dfs(int v, int p = -1) {
    used[v] = 1;
    h[v] = d[v] = (p == -1 ? 0 : h[p] + 1);
    for (auto [u, id] : g[v]) {
        if (used_edge[id]) continue;
        if (used[u] == 0) {
            used_edge[id] = 1;
            dfs(u, v);
            d[v] = min(d[v], d[u]);
            if (h[v] < d[u]) is_bridge[id] = 1;
        } else if (used[u] == 1) {
            d[v] = min(d[v], h[u]);
        }
    }
    used[v] = 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, cnt = 0; cin >> n >> m;
    vector <pair <int, int>> edges;
    if (2 * (n - 1) < m) {
        cout << "! No\n" << flush;
        return 0;
    }
    g.resize(n), used.resize(n), used_edge.resize(m), h.resize(n), d.resize(n), is_bridge.resize(m);
    for (int i = 0, u; i < n; i++) {
        while (true) {
            cout << "? " << i + 1 << '\n' << flush;
            cin >> u;
            if (u == -1) break;
            u--;
            if (i != u) {
                edges.push_back({i, u});
                g[i].push_back({u, cnt});
                g[u].push_back({i, cnt++});
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (!used[i]) dfs(i);
    }
    int need = (m - 1) / 2 + 1; cnt = 0;
    for (int u : is_bridge) cnt += u;
    if (cnt < need) {
        cout << "! No\n" << flush;
        return 0;
    }
    cout << "! Yes\n" << flush;
    for (int i = 0; i < m && need; i++) {
        if (is_bridge[i]) cout << edges[i].first + 1 << ' ' << edges[i].second + 1 << '\n' << flush, need--;
    }
    return 0;
}