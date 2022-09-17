#include <bits/stdc++.h>
using namespace std;

struct edge {
    int v, u, f, c, id;

    edge(int v, int u, int c, int id) : v(v), u(u), f(0), c(c), id(id) {};
    int get_cap() { return c - f; }
};

vector <edge> e;
vector <vector <int>> g;
vector <int> p, ans;

void add_edge(int v, int u, int c, int id) {
    g[v].push_back(e.size());
    e.push_back(edge(v, u, c, id));
    g[u].push_back(e.size());
    e.push_back(edge(u, v, c, id));
}

int bfs(int s, int t) {
    queue <int> q;
    q.push(s);
    int min_cap = INT_MAX;
    p.assign(p.size(), -1);
    p[s] = -2;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int u : g[v]) {
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
        e[p[t] ^ 1].f += min_cap;
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
        add_edge(v, u, c, i);
    }
    while (bfs(0, n - 1));
    int sum = 0;
    for (auto u : g[0]) sum += e[u].f;
    for (int i = 0; i < n; i++) {
        if (p[i] == -1) continue;
        for (auto u : g[i]) {
            if (p[e[u].u] == -1) ans.push_back(e[u].id);
        }
    }
    cout << ans.size() << ' ' << sum << '\n';
    for (auto u : ans) cout << u + 1 << ' ';
    return 0;
}