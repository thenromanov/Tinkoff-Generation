#include <bits/stdc++.h>
using namespace std;

pair <int, int> dfs(vector <vector <int>>& g, int v, int p = -1, int h = 0) {
    pair <int, int> ans = {h, v};
    for (int u : g[v]) {
        if (u == p) continue;
        ans = max(ans, dfs(g, u, v, h + 1));
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    vector <vector <int>> g1(n);
    for (int i = 0, v, u; i < n - 1; i++) {
        cin >> v >> u; v--, u--;
        g1[v].push_back(u);
        g1[u].push_back(v);
    }
    pair <int, int> ans1 = dfs(g1, 0);
    pair <int, int> ans2 = dfs(g1, ans1.second);
    int m; cin >> m;
    vector <vector <int>> g2(m);
    for (int i = 0, v, u; i < m - 1; i++) {
        cin >> v >> u; v--, u--;
        g2[v].push_back(u);
        g2[u].push_back(v);
    }
    pair <int, int> ans3 = dfs(g2, 0);
    pair <int, int> ans4 = dfs(g2, ans3.second);
    cout << (ans4.first < ans2.first - ans2.first / 2 ? "GGEZ\n" : "FF\n");
    return 0;
}