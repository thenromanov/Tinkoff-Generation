#include <bits/stdc++.h>
using namespace std;

const int maxs = 16;

int k, n, m;
vector <vector <int>> g, used;
vector <pair <int, int>> d = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
vector <int> mx(maxs);

bool check(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= m || used[x][y]) return false;
    for (int i = 0; i < maxs; i++) {
        bool ok = true;
        for (int j = 0; j < 4; j++) {
            if (((i >> j) & 1) == 1 && (x + d[j].first < 0 || x + d[j].first >= n || y + d[j].second < 0 || y + d[j].second >= m || !used[x + d[j].first][y + d[j].second])) {
                ok = false;
                break;
            }
        }
        if (ok && mx[i] >= g[x][y]) return true;
    }
    return false;
}

pair <int, int> ans = {INT_MAX, 0};

void relax(const pair <int, int>& b) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) used[i][j] = 0;
    }
    queue <pair <int, int>> q;
    q.push(b);
    used[b.first][b.second] = 1;
    int cur = 1;
    while (!q.empty()) {
        auto [i, j] = q.front();
        q.pop();
        for (auto [x, y] : d) {
            if (check(i + x, j + y)) {
                used[i + x][j + y] = 1;
                q.push({i + x, j + y});
                cur++;
            }
        }
    }
    if (cur < ans.first) ans = {cur, 1};
    else if (cur == ans.first) ans.second++;
}

void relax2(const pair <int, int>& b) {
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

void solve1(string& s) {
    g.resize(n, vector <int> (m));
    used.resize(n, vector <int> (m));
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
            relax2({i, j});
        }
    }
    cout << ans.first << '\n' << ans.second << '\n';
}

void solve2(string& s) {
    vector <pair <int, int>> order;
    for (int i = 0; i < 2 * k; i++) {
        int cur = 0;
        if (s[i % k] == 'W') cur = 1;
        else if (s[i % k] == 'S') cur = 2;
        else if (s[i % k] == 'E') cur = 3;
        if (order.empty() || order.back().first != cur) order.push_back({cur, 1});
        else order.back().second++;
    }
    for (int i = 0; i < maxs; i++) {
        int cur = 0;
        for (int j = 0; j < (int)order.size(); j++) {
            if ((i >> order[j].first) & 1) cur += order[j].second;
            else mx[i] = max(mx[i], cur), cur = 0;
        }
        mx[i] = max(mx[i], cur);
        if (cur == 2 * k) mx[i] = INT_MAX - 1;
    }
    g.resize(n, vector <int> (m)), used.resize(n, vector <int> (m));
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
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> k >> n >> m;
    string s; cin >> s;
    int cnt = 0;
    for (auto& u : s) cnt += (u == 'N' || u == 'S');
    if (cnt == 0) solve1(s);
    else solve2(s);
    return 0;
}