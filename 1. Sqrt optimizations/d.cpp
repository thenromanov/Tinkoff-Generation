#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, ans = 0; cin >> n >> m;
    vector <vector <int>> g(n);
    for (int i = 0, v, u; i < m; i++) {
        cin >> v >> u;
        g[v - 1].push_back(u - 1);
        g[u - 1].push_back(v - 1);
    }
    auto cmp = [&](int a, int b) {return ((int)g[a].size() == (int)g[b].size()) ? a > b : (int)g[a].size() > (int)g[b].size();};
    vector <int> cnt(n);
    for (int v = 0; v < n; v++) {
        for (int u : g[v]) {
            if (cmp(v, u)) cnt[u]++;
        }
        for (int u : g[v]) {
            if (cmp(v, u)) {
                for (int w : g[u]) {
                    if (cmp(u, w)) ans += cnt[w];
                }
            }
        }
        for (int u : g[v]) {
            if (cmp(v, u)) cnt[u]--;
        }
    }
    cout << ans;
    return 0;
}