#include <bits/stdc++.h>
using namespace std;

vector <vector <int>> g;
vector <int> used, par, sz;

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
        if (u != p) {
            if (!used[u] && sz[u] > n / 2) return find_centroid(u, v, n);
        }
    }
    return v;
}

void decompose(int v, int p) {
   find_size(v);
   int c = find_centroid(v, -1, sz[v]);
   used[c] = 1, par[c] = p;
   for (int u : g[c]) {
       if (!used[u]) decompose(u, c);
   }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    g.resize(n), used.resize(n), par.resize(n), sz.resize(n);
    for (int i = 0, v, u; i < n - 1; i++) {
        cin >> v >> u; v--, u--;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    decompose(0, -1);
    for (int u : par) cout << u + 1 << ' ';
    return 0;
}