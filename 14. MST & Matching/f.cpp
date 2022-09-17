#include <bits/stdc++.h>
using namespace std;

const int logn = 21;

vector <vector <int>> g, up;
vector <int> a;
int64_t ans = 0;

void dfs(int v, int p = -1) {
    up[0][v] = (p == -1 ? v : p);
    for (int l = 1; l < logn; l++) up[l][v] = up[l - 1][up[l - 1][v]];
    int64_t mn = LLONG_MAX;
    for (int l = 0; l < logn; l++) mn = min(mn, (int64_t)(l + 1) * a[up[l][v]] + a[v]);
    if (p != -1) ans += mn;
    for (int u : g[v]) {
        if (u == p) continue;
        dfs(u, v);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    g.resize(n), up.resize(logn, vector <int> (n)), a.resize(n);
    for (int& u : a) cin >> u;
    int s = min_element(a.begin(), a.end()) - a.begin();
    for (int i = 0, v, u; i < n - 1; i++) {
        cin >> v >> u; v--, u--;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    dfs(s);
    cout << ans << '\n';
    return 0;
}