#include <bits/stdc++.h>
using namespace std;

vector <vector <int>> g;
vector <int> used, sz, color;
vector <vector <pair <int, int>>> par;
vector <unordered_map <int, int>> dist;

int find_size(int v, int p = -1) {
    if (used[v]) return 0;
    sz[v] = 1;
    for (int u : g[v]) {
        if (u != p) sz[v] += find_size(u, v);
    }
    return sz[v];
}

int find_centroid(int v, int p, int n) {
    for (int u : g[v]) {
        if (u != p && !used[u] && sz[u] > n / 2) return find_centroid(u, v, n);
    }
    return v;
}

void find_dist(int v, int p, int c, int h = 0) {
    if (used[v]) return;
    par[v].push_back({c, h});
    if (dist[c].find(color[v]) == dist[c].end()) dist[c][color[v]] = h;
    else dist[c][color[v]] = min(dist[c][color[v]], h);
    for (int u : g[v]) {
        if (u != p) find_dist(u, v, c, h + 1);
    }
}

void decompose(int v, int p = -1) {
    find_size(v);
    int c = find_centroid(v, -1, sz[v]);
    find_dist(c, -1, c);
    used[c] = 1;
    for (int u : g[c]) {
        if (!used[u]) decompose(u, c);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    g.resize(n), used.resize(n), sz.resize(n), color.resize(n), par.resize(n), dist.resize(n);
    for (int i = 1, v; i < n; i++) {
        cin >> v;
        g[v].push_back(i);
        g[i].push_back(v);
    }
    for (int i = 0; i < n; i++) cin >> color[i];
    decompose(0);
    int q; cin >> q;
    while (q--) {
        int v, c, mn = INT_MAX; cin >> v >> c;
        for (auto [u, l] : par[v]) {
            if (dist[u].find(c) != dist[u].end()) {
                mn = min(mn, l + dist[u][c]);
            }
        }
        cout << (mn == INT_MAX ? -1 : mn) << ' ';
    }
    return 0;
}