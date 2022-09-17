#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e5 + 7;
const int logn = 20;
const int mod = 1e9 + 7;

vector <vector <int>> g(maxn), up(logn, vector <int> (maxn));
vector <vector <pair <int, int>>> g2(maxn);
vector <int> h(maxn), d(maxn), clr(maxn, -1), tin(maxn), tout(maxn);
int tmr = 0;

bool is_anc(int v, int u) {
    return tin[v] <= tin[u] && tout[u] <= tout[v];
}

int lca(int v, int u) {
    if (is_anc(v, u)) return v;
    if (is_anc(u, v)) return u;
    int cur = v;
    for (int l = logn - 1; l >= 0; l--) {
        if (!is_anc(up[l][cur], u)) cur = up[l][cur];
    }
    return up[0][cur];
}

void fill_tmr(int v, int p = -1) {
    tin[v] = tmr++;
    d[v] = h[v] = (p == -1 ? 0 : h[p] + 1);
    up[0][v] = (p == -1 ? 0 : p);
    for (int l = 1; l < logn; l++) up[l][v] = up[l - 1][up[l - 1][v]];
    for (int u : g[v]) {
        if (u != p) fill_tmr(u, v);
    }
    tout[v] = tmr++;
}

void make_graph(int v, int p = -1) {
    for (int u : g[v]) {
        if (u != p) {
            make_graph(u, v);
            d[v] = min(d[v], d[u]);
            if (d[u] < h[v]) {
                g2[v].push_back({u, 0});
                g2[u].push_back({v, 0});
            }
        }
    }
}

bool check(int v, int c) {
    if (clr[v] != -1) return (clr[v] == c);
    clr[v] = c;
    for (auto [u, op] : g2[v]) {
        bool res = check(u, c ^ op);
        if (!res) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m; cin >> n >> m;
    for (int i = 0, v, u; i < n - 1; i++) {
        cin >> v >> u; v--, u--;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    fill_tmr(0);
    for (int i = 0, v, u; i < m; i++) {
        cin >> v >> u; v--, u--;
        int c = lca(v, u);
        d[v] = min(d[v], h[c]);
        d[u] = min(d[u], h[c]);
        if (v != c && u != c) {
            g2[v].push_back({u, 1});
            g2[u].push_back({v, 1});
        }
    }
    make_graph(0);
    int ans = 1;
    for (int i = 1; i < n; i++) {
        if (clr[i] == -1) {
            bool res = check(i, 0);
            if (!res) {
                cout << 0 << '\n';
                return 0;
            }
            ans = ans * 2 % mod;
        }
    }
    cout << ans << '\n';
    return 0;
}