#include <bits/stdc++.h>
using namespace std;

vector <vector <int>> c;

bool dfs(int v, vector <vector <int>>& g, vector <int>& mt, vector <int>& used) {
    if (used[v]) return false;
    used[v] = true;
    for (int u : g[v]) {
        if (mt[u] == -1 || dfs(mt[u], g, mt, used)) {
            mt[u] = v;
            return true;
        }
    }
    return false;
}

bool solve(int n, int m, int mid) {
    vector <vector <int>> g(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (c[i][j] >= mid) g[i].push_back(j);
        }
    }
    int ans = 0;
    vector <int> used(n), mt(m, -1);
    for (int i = 0; i < n; i++) {
        if (dfs(i, g, mt, used)) ans++, used.assign(n, 0);
    }
    return (ans == min(n, m));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m; cin >> n >> m;
    c.resize(n, vector <int> (m));
    for (auto& u : c) {
        for (int& i : u) cin >> i;
    }
    int l = 0, r = 1e9 + 1;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (solve(n, m, mid)) l = mid;
        else r = mid;
    }
    cout << l << '\n';
    return 0;
}