#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m; cin >> n >> m;
    vector <int> cost(2 * n + 2 * m - 2);
    vector <vector <vector <int>>> pos(n, vector <vector <int>> (m));
    vector <vector <pair <int, int>>> cols(2 * n + 2 * m - 2);
    for (int i = 0; i < m + n - 1; i++) {
        int64_t c; cin >> c;
        cost[i] = c;
        for (int x = 0; x < n; x++) {
            for (int y = m - 1; y >= 0; y--) {
                if (m - 1 + x - y == i) {
                    pos[x][y].push_back(i);
                    cols[i].push_back({x, y});
                }
            }
        }
    }
    for (int i = 0; i < m + n - 1; i++) {
        int64_t c; cin >> c;
        cost[i + m + n - 1] = c;
        for (int x = 0; x < n; x++) {
            for (int y = 0; y < m; y++) {
                if (x + y == i) {
                    pos[x][y].push_back(i + n + m - 1);
                    cols[i + n + m - 1].push_back({x, y});
                }
            }
        }
    }
    vector <vector <int>> best(n, vector <int> (m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int mcos = INT_MAX;
            for (int u : pos[i][j]) {
                if (cost[u] < mcos) {
                    mcos = cost[u];
                    best[i][j] = u;
                }
            }
        }
    }
    vector <int> use(2 * n + 2 * m - 2, 0);
    for (int i = 0; i < 2 * n + 2 * m - 2; i++) {
        int cnt = 0;
        if (use[i]) continue;
        for (auto u : cols[i]) {
            if (best[u.first][u.second] == i) cnt++;
        }
        if (cnt >= (cols[i].size() + 1) / 2) {
            use[i] = 1;
        } else {
            for (auto u : cols[i]) {
                if (best[u.first][u.second] != i) use[best[u.first][u.second]] = 1;
            }
        }
    }
    int64_t ans = 0;
    for (int i = 0; i < 2 * n + 2 * m - 2; i++) {
        if (use[i]) ans += cost[i];
    }
    cout << ans;
    return 0;
}