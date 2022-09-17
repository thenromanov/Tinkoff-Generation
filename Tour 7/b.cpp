#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 179;
const int logn = 19;

int t = 0, res = 0;
vector <vector <int>> g(maxn), up(logn, vector <int> (maxn));
vector <int> tin(maxn), tout(maxn), dp(maxn), depth(maxn);

bool is_anc(int v, int u) {
    return tin[v] <= tin[u] && tout[u] <= tout[v];
}

void get_times(int v, int p = -1) {
    tin[v] = t++;
    if (p != -1) depth[v] = depth[p] + 1;
    up[0][v] = (p == -1 ? 0 : p);
    for (int l = 1; l < logn; l++) up[l][v] = up[l - 1][up[l - 1][v]];
    for (int u : g[v]) {
        if (u != p) get_times(u, v);
    }
    tout[v] = t++;
}

int first_prev(int v, int u) {
    for (int l = logn - 1; l >= 0; l--) {
        int to = up[l][u];
        if (depth[v] < depth[to]) u = to;
    }
    return u;
}

void dfs(int v, int p, int s) {
    s += dp[v];
    res = max(res, s);
    for (int u : g[v]) {
        if (u != p) dfs(u, v, s);
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    for (int i = 0, v, u; i < n - 1; i++) {
        cin >> v >> u; v--, u--;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    get_times(0);
    int m, cnt = 0; cin >> m;
    for (int i = 0, v, u; i < m; i++) {
        cin >> v >> u; v--, u--;
        if (is_anc(v, u)) {
            int to = first_prev(v, u);
            dp[to]--;
            dp[u]++;
            cnt++;
        } else if (is_anc(u, v)) {
            int to = first_prev(u, v);
            dp[to]--;
            dp[v]++;
            cnt++;
        } else {
            dp[v]++;
            dp[u]++;
        }
    }
    dfs(0, -1, 0);
    cout << res + cnt;
    return 0;
}