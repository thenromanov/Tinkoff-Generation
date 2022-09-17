#include <bits/stdc++.h>
using namespace std;

struct dsu {
    int cnt;
    vector <int> p, sz;

    dsu(int n) {
        p.resize(n), sz.resize(n, 1);
        iota(p.begin(), p.end(), 0);
        cnt = n;
    }

    int find(int v) {
        if (p[v] == v) return v;
        return p[v] = find(p[v]);
    }

    void unite(int v, int u) {
        v = find(v), u = find(u);
        if (v == u) return;
        if (sz[v] > sz[u]) swap(v, u);
        sz[u] += sz[v];
        p[v] = u;
        cnt--;
    }

    int get_cnt() {
        return cnt;
    }
};

int64_t dijkstra(vector <vector <pair <int, int>>>& g, int s, int e, int n) {
    priority_queue <pair <int64_t, int>, vector <pair <int64_t, int>>, greater <pair <int64_t, int>>> q;
    vector <int64_t> d(n, LLONG_MAX);
    d[s] = 0;
    q.push({0, s});
    while (!q.empty()) {
        auto [curd, v] = q.top();
        q.pop();
        if (curd > d[v]) continue;
        for (auto [u, c] : g[v]) {
            if (d[u] > d[v] + c) {
                d[u] = d[v] + c;
                q.push({d[u], u});
            }
        }
    }
    return d[e];
}

void solve1() {
    int n1, m1; cin >> n1 >> m1;
    vector <vector <pair <int, int>>> g1(n1);
    for (int i = 0, v, u, c; i < m1; i++) {
        cin >> v >> u >> c; v--, u--;
        g1[v].push_back({u, c});
        g1[u].push_back({v, c});
    }
    int n2, m2; cin >> n2 >> m2;
    vector <vector <pair <int, int>>> g2(n2);
    for (int i = 0, v, u, c; i < m2; i++) {
        cin >> v >> u >> c; v--, u--;
        g2[v].push_back({u, c});
        g2[u].push_back({v, c});
    }
    cout << dijkstra(g1, 0, n1 - 1, n1) + dijkstra(g2, 0, n2 - 1, n2) << '\n';
}

void solve2() {
    int n1, m1; cin >> n1 >> m1;
    vector <pair <pair <int, int>, pair <int, int>>> g;
    for (int i = 0, v, u, c; i < m1; i++) {
        cin >> v >> u >> c; v--, u--;
        g.push_back({{c, 0}, {v, u}});
    }
    int n2, m2; cin >> n2 >> m2;
    for (int i = 0, v, u, c; i < m2; i++) {
        cin >> v >> u >> c; v--, u--;
        g.push_back({{c, 1}, {v, u}});
    }
    sort(g.begin(), g.end());
    dsu xs(n1), ys(n2);
    int64_t ans = 0;
    for (auto e : g) {
        auto [c, t] = e.first;
        auto [v, u] = e.second;
        if (t == 0) {
            v = xs.find(v), u = xs.find(u);
            if (v == u) continue;
            xs.unite(v, u);
            ans += 1LL * c * ys.get_cnt();
        } else {
            v = ys.find(v), u = ys.find(u);
            if (v == u) continue;
            ys.unite(v, u);
            ans += 1LL * c * xs.get_cnt();
        }
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t; cin >> t;
    if (t == 1) solve1();
    else solve2();
    return 0;
}