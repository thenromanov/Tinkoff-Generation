#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m; cin >> n >> m;
    vector <vector <int64_t>> h(n, vector <int64_t> (m)), d(n, vector <int64_t> (m, LLONG_MAX));
    vector <pair <int, int>> dts = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    priority_queue <pair <int64_t, pair <int, int>>, vector <pair <int64_t, pair <int, int>>>, greater <pair <int64_t, pair <int, int>>>> q;
    for (auto& i : h) for (int64_t& j : i) cin >> j;
    for (int i = 0; i < n; i++) {
        d[i][0] = h[i][0];
        d[i][m - 1] = h[i][m - 1];
        q.push({d[i][0], {i, 0}});
        q.push({d[i][m - 1], {i, m - 1}});
    }
    for (int j = 0; j < m; j++) {
        d[0][j] = h[0][j];
        d[n - 1][j] = h[n - 1][j];
        q.push({d[0][j], {0, j}});
        q.push({d[n - 1][j], {n - 1, j}});
    }
    while (!q.empty()) {
        int64_t cur = q.top().first;
        auto [x, y] = q.top().second;
        q.pop();
        if (cur > d[x][y]) continue;
        for (auto u : dts) {
            if (x + u.first >= 0 && x + u.first < n && y + u.second >= 0 && y + u.second < m && d[x + u.first][y + u.second] > max(d[x][y], h[x + u.first][y + u.second])) {
                d[x + u.first][y + u.second] = max(d[x][y], h[x + u.first][y + u.second]);
                q.push({d[x + u.first][y + u.second], {x + u.first, y + u.second}});
            }
        }
    }
    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ans += d[i][j] - h[i][j];
        }
    }
    cout << ans << '\n';
    return 0;
}