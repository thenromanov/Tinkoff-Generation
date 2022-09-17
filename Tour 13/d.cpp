#include <bits/stdc++.h>
using namespace std;

int n, m;
vector <vector <int>> g, used;
vector <int> mx(4);
vector <pair <int, int>> d = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
pair <int, int> ans = {INT_MAX, 0};

void relax(const pair <int, int>& b) {
    for (int j = 0; j < m; j++) used[b.first][j] = 0;
    queue <pair <int, int>> q;
    q.push(b);
    used[b.first][b.second] = 1;
    int cur = 1;
    while (!q.empty()) {
        auto [i, j] = q.front();
        q.pop();
        for (int o = 1; o < 4; o += 2) {
            auto [x, y] = d[o];
            if (i + x >= 0 && i + x < n && j + y >= 0 && j + y < m && !used[i + x][j + y] && g[i + x][j + y] <= mx[o]) {
                used[i + x][j + y] = 1;
                q.push({i + x, j + y});
                cur++;
            }
        }
    }
    if (cur < ans.first) ans = {cur, 1};
    else if (cur == ans.first) ans.second++;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int k; cin >> k >> n >> m;
    g.resize(n, vector <int> (m));
    used.resize(n, vector <int> (m));
    string s; cin >> s;
    vector <pair <char, int>> order;
    for (int i = 0; i < 2 * k; i++) {
        if (order.empty() || order.back().first != s[i % k]) order.push_back({s[i % k], 1});
        else order.back().second++;
    }
    for (auto u : order) {
        if (u.first == 'S') mx[0] = (order.size() == 1 ? INT_MAX - 1 : max(min(mx[0], k), u.second));
        else if (u.first == 'E') mx[1] = (order.size() == 1 ? INT_MAX - 1 : max(min(mx[1], k), u.second));
        else if (u.first == 'N') mx[2] = (order.size() == 1 ? INT_MAX - 1 : max(min(mx[2], k), u.second));
        else mx[3] = (order.size() == 1 ? INT_MAX - 1 : max(min(mx[3], k), u.second));
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> g[i][j];
            if (g[i][j] == 0) g[i][j] = INT_MAX;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] == INT_MAX) continue;
            relax({i, j});
        }
    }
    cout << ans.first << '\n' << ans.second << '\n';
    return 0;
}