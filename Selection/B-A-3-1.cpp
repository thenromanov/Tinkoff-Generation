#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m; cin >> n >> m;
    vector <string> v(n);
    for (string& u : v) cin >> u;
    vector <vector <int>> g(n, vector <int> (m)), used(n, vector <int> (m));
    int cur = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (v[i][j] == '.') g[i][j] = -1e9;
            else if (v[i][j] == 'S') g[i][j] = -1;
        }
    }
    queue <pair <int, int>> qu;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (v[i][j] == 'X' && !used[i][j]) {
                qu.push({i, j});
                used[i][j] = 1;
                while (!qu.empty()) {
                    auto [x, y] = qu.front();
                    qu.pop();
                    g[x][y] = cur;
                    if (x + 1 < n && v[x + 1][y] == 'X' && !used[x + 1][y]) {
                        used[x + 1][y] = 1;
                        qu.push({x + 1, y});
                    }
                    if (x - 1 >= 0 && v[x - 1][y] == 'X' && !used[x - 1][y]) {
                        used[x - 1][y] = 1;
                        qu.push({x - 1, y});
                    }
                    if (y + 1 < m && v[x][y + 1] == 'X' && !used[x][y + 1]) {
                        used[x][y + 1] = 1;
                        qu.push({x, y + 1});
                    }
                    if (y - 1 >= 0 && v[x][y - 1] == 'X' && !used[x][y - 1]) {
                        used[x][y - 1] = 1;
                        qu.push({x, y - 1});
                    }
                }
                cur++;
            }
        }
    }
    vector <vector <int>> t(cur, vector <int> (cur, 1e5));
    vector <vector <int>> d(n, vector <int> (m, 1e5)), was(n, vector <int> (m));
    for (int i = 0; i < cur; i++) t[i][i] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] < 0) continue;
            d.assign(n, vector <int> (m, 1e5));
            was.assign(n, vector <int> (m, 0));
            d[i][j] = 0;
            was[i][j] = 1;
            qu.push({i, j});
            while (!qu.empty()) {
                auto [x, y] = qu.front(); 
                qu.pop();
                if (x + 1 < n && !was[x + 1][y]) {
                    was[x + 1][y] = 1;
                    if (g[x + 1][y] == -1) {
                        d[x + 1][y] = d[x][y] + 1;
                        qu.push({x + 1, y});
                    } else if (g[x + 1][y] >= 0) {
                        t[g[i][j]][g[x + 1][y]] = min(t[g[i][j]][g[x + 1][y]], d[x][y]);
                    }
                }
                if (x - 1 >= 0 && !was[x - 1][y]) {
                    was[x - 1][y] = 1;
                    if (g[x - 1][y] == -1) {
                        d[x - 1][y] = d[x][y] + 1;
                        qu.push({x - 1, y});
                    } else if (g[x - 1][y] >= 0) {
                        t[g[i][j]][g[x - 1][y]] = min(t[g[i][j]][g[x - 1][y]], d[x][y]);
                    }
                }
                if (y + 1 < m && !was[x][y + 1]) {
                    was[x][y + 1] = 1;
                    if (g[x][y + 1] == -1) {
                        d[x][y + 1] = d[x][y] + 1;
                        qu.push({x, y + 1});
                    } else if (g[x][y + 1] >= 0) {
                        t[g[i][j]][g[x][y + 1]] = min(t[g[i][j]][g[x][y + 1]], d[x][y]);
                    }
                }
                if (y - 1 >= 0 && !was[x][y - 1]) {
                    was[x][y - 1] = 1;
                    if (g[x][y - 1] == -1) {
                        d[x][y - 1] = d[x][y] + 1;
                        qu.push({x, y - 1});
                    } else if (g[x][y - 1] >= 0) {
                        t[g[i][j]][g[x][y - 1]] = min(t[g[i][j]][g[x][y - 1]], d[x][y]);
                    }
                }
            }
        }
    }
    vector <vector <int>> cost(cur, vector <int> (1 << cur, 1e5));
    for (int i = 0; i < cur; i++) {
        qu.push({i, 1 << i});
        cost[i][1 << i] = 0;
    }
    while (!qu.empty()) {
        auto [u, mask] = qu.front();
        qu.pop();
        for (int to = 0; to < cur; to++) {
            if (u == to) continue;
            if (cost[to][mask | (1 << to)] > cost[u][mask] + t[u][to]) {
                qu.push({to, mask | (1 << to)});
                cost[to][mask | (1 << to)] = cost[u][mask] + t[u][to];
            }
        }
    }
    int ans = INT_MAX;
    for (int i = 0; i < cur; i++) ans = min(ans, cost[i][(1 << cur) - 1]);
    cout << ans;
    return 0;
}