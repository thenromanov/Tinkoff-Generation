#include <bits/stdc++.h>
using namespace std;

int n, m;
vector <string> y;
vector <pair <int, int>> xs;
vector <vector <int>> g;
vector <int> p, s;

void bfs(pair <int, int> s) {
    vector <vector <int>> d(n, vector <int> (m, 1e5)), used(n, vector <int> (m));
    d[s.first][s.second] = 0;
    used[s.first][s.second] = 1;
    queue <pair <int, int>> q;
    q.push(s);
    while (!q.empty()) {
        auto [i, j] = q.front();
        q.pop();
        if (i + 1 < n && !used[i + 1][j]) {
            if (y[i + 1][j] == 'S') {
                d[i + 1][j] = d[i][j] + 1;
                used[i + 1][j] = 1;
                q.push({i + 1, j});
            } else if (y[i + 1][j] == 'X') {
                g[int(lower_bound(xs.begin(), xs.end(), s) - xs.begin())].push_back({int(lower_bound(xs.begin(), xs.end(), make_pair(i + 1, j)) - xs.begin()), d[i][j]});
            }
        }
        if (i - 1 >= 0 && !used[i - 1][j]) {
            if (y[i - 1][j] == 'S') {
                d[i - 1][j] = d[i][j] + 1;
                used[i - 1][j] = 1;
                q.push({i - 1, j});
            } else if (y[i - 1][j] == 'X') {
                g[int(lower_bound(xs.begin(), xs.end(), s) - xs.begin())].push_back({int(lower_bound(xs.begin(), xs.end(), make_pair(i - 1, j)) - xs.begin()), d[i][j]});
            }
        }
        if (j + 1 < m && !used[i][j + 1]) {
            if (y[i][j + 1] == 'S') {
                d[i][j + 1] = d[i][j] + 1;
                used[i][j + 1] = 1;
                q.push({i, j + 1});
            } else if (y[i][j + 1] == 'X') {
                g[int(lower_bound(xs.begin(), xs.end(), s) - xs.begin())].push_back({int(lower_bound(xs.begin(), xs.end(), make_pair(i, j + 1)) - xs.begin()), d[i][j]});
            }
        }
        if (j - 1 >= 0 && !used[i][j - 1]) {
            if (y[i][j - 1] == 'S') {
                d[i][j - 1] = d[i][j] + 1;
                used[i][j - 1] = 1;
                q.push({i, j - 1});
            } else if (y[i][j - 1] == 'X') {
                g[int(lower_bound(xs.begin(), xs.end(), s) - xs.begin())].push_back({int(lower_bound(xs.begin(), xs.end(), make_pair(i, j - 1)) - xs.begin()), d[i][j]});
            }
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    y.resize(n);
    for (string& u : y) cin >> u;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (y[i][j] == 'X') xs.push_back(make_pair(i, j));
        }
    }
    sort(xs.begin(), xs.end());
    for (auto u : xs) bfs(u);
    p.resize(xs.size()), s.resize(xs.size());
    for (int i = 0; i < xs.size(); i++) p[i] = i, s[i] = 1;
    sort(g.begin(), g.end());
    int ans = 0;
    for (auto u : g) {
        if (find(u[1]) != find(u[2])) {
            ans += u[0];
            unite(u[1], u[2]);
        }
    }
    cout << ans;
    return 0;
}