#include <bits/stdc++.h>
using namespace std;

const int64_t inf = 1e14 + 7;

vector <vector <pair <int, int>>> g;

vector <int64_t> dijkstra(int s, int n) {
    vector <int64_t> d(n, inf);
    priority_queue <pair <int64_t, int>, vector <pair <int64_t, int>>, greater <pair <int64_t, int>>> q;
    d[s] = 0;
    q.push({0, s});
    while (!q.empty()) {
        int64_t cur = q.top().first;
        int v = q.top().second;
        q.pop();
        if (cur > d[v]) continue;
        for (auto [u, c] : g[v]) {
            if (d[v] + c < d[u]) {
                d[u] = d[v] + c;
                q.push({d[u], u});
            }
        }
    }
    return d;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, s, t, v, u; cin >> n >> m >> s >> t >> v >> u;
    g.resize(n);
    s--, t--, v--, u--;
    for (int i = 0, a, b, c; i < m; i++) {
        cin >> a >> b >> c; a--, b--;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }
    vector <int64_t> dv = dijkstra(v, n), du = dijkstra(u, n);
    vector <int64_t> d(n, inf);
    vector <pair <int64_t, int64_t>> best(n, {inf, inf});
    priority_queue <pair <int64_t, int>, vector <pair <int64_t, int>>, greater <pair <int64_t, int>>> q;
    d[s] = 0; q.push({0, s}); best[s] = {dv[s], du[s]};
    while (!q.empty()) {
        int64_t cur = q.top().first;
        int v = q.top().second;
        q.pop();
        if (cur > d[v]) continue;
        for (auto [u, c] : g[v]) {
            if (d[v] + c < d[u]) {
                d[u] = d[v] + c;
                best[u].first = min(best[v].first, dv[u]);
                best[u].second = min(best[v].second, du[u]);
                q.push({d[u], u});
            } else if (d[v] + c == d[u] && min(dv[u], best[v].first) + min(du[u], best[v].second) < best[u].first + best[u].second) {
                best[u].first = min(best[v].first, dv[u]);
                best[u].second = min(best[v].second, du[u]);
            }
        }
    }
    cout << min(best[t].first + best[t].second, dv[u]) << '\n';
    return 0;
}