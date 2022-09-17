#include <bits/stdc++.h>
using namespace std;

struct dsu {
    vector <int> p, sz;
    int cnt;

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

    int get_count() {
        return cnt;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m; cin >> n >> m;
    vector <string> g(n);
    for (auto& u : g) cin >> u;
    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        dsu d(n * m);
        int cnt0 = 0;
        for (int j = i; j < n; j++) {
            for (int k = 0; k < m; k++) {
                if (g[j][k] == '0') {
                    cnt0++;
                    continue;
                }
                if (k - 1 >= 0 && g[j][k - 1] == '1' && g[j][k] == '1') d.unite(j * m + k - 1, j * m + k);
                if (j - 1 >= i && g[j - 1][k] == '1' && g[j][k] == '1') d.unite((j - 1) * m + k, j * m + k);
            }
            ans += d.get_count() - cnt0 - i * m - (n - 1 - j) * m;
        }
    }
    cout << ans << '\n';
    return 0;
}