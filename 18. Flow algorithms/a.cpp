#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9 + 7;

struct edge {
    int v, u, f, c;

    edge(int v, int u, int c) : v(v), u(u), f(0), c(c) {};
    int get_cap() { return c - f; }
};

vector <edge> e;
vector <vector <int>> g;
vector <int> p;

void add_edge(int v, int u, int c) {
    g[v].push_back(e.size());
    e.push_back(edge(v, u, c));
    g[u].push_back(e.size());
    e.push_back(edge(u, v, 0));
}

int bfs(int s, int t) {
    queue <int> q;
    q.push(s);
    int min_cap = inf;
    p.assign(p.size(), -1);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto u : g[v]) {
            if (e[u].get_cap() == 0) continue;
            if (p[e[u].u] != -1) continue;
            min_cap = min(min_cap, e[u].get_cap());
            q.push(e[u].u);
            p[e[u].u] = u;
        }
    }
    if (p[t] == -1) return 0;
    while (t != s) {
        e[p[t]].f += min_cap;
        e[p[t] ^ 1].f -= min_cap;
        t = e[p[t]].v;
    }
    return 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m; cin >> n >> m;
    g.resize(n), p.resize(n);
    for (int i = 0, v, u, c; i < m; i++) {
        cin >> v >> u >> c; v--, u--;
        add_edge(v, u, c);
    }
    while (bfs(0, n - 1));
    int ans = 0;
    for (auto u : g[0]) ans += e[u].f;
    cout << ans << '\n';
    return 0;
}