#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m; cin >> n >> m;
    vector <vector <int>> a(n, vector <int> (m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cin >> a[i][j];
    }
    if (n == 1 && m == 1) {
        if (a[0][0] >= 0) cout << 1 << ' ' << 1 << '\n';
        else cout << -1 << '\n';
        return 0;
    }
    if (n % 2 && m % 2) {
        cout << -1;
        return 0;
    }
    vector <pair <int, int>> order;
    if (n % 2 == 0) {
        for (int i = 0; i < n; i++) order.push_back({i, 0});
        for (int i = n - 1; i >= 0; i--) {
            if (i % 2) for (int j = 1; j < m; j++) order.push_back({i, j});
            else for (int j = m - 1; j > 0; j--) order.push_back({i, j});
        }
    } else {
        for (int j = 0; j < m; j++) order.push_back({0, j});
        for (int j = m - 1; j >= 0; j--) {
            if (j % 2) for (int i = 1; i < n; i++) order.push_back({i, j});
            else for (int i = n - 1; i > 0; i--) order.push_back({i, j});
        }
    }
    int mn = INT_MAX, pos = -1;
    for (int i = 0; i < n * m; i++) {
        if (mn >= a[order[i].first][order[i].second]) {
            mn = a[order[i].first][order[i].second];
            pos = i;
        }
    }
    pos = (pos + 1) % (n * m);
    int64_t sum = 0;
    for (int i = 0; i < n * m + 1; i++) {
        sum += a[order[(pos + i) % (n * m)].first][order[(pos + i) % (n * m)].second];
        if (sum < 0) {
            cout << -1 << '\n';
            return 0;
        }
    }
    for (int i = 0; i < n * m; i++) cout << order[(pos + i) % (n * m)].first + 1 << ' ' << order[(pos + i) % (n * m)].second + 1 << '\n';
    return 0;
}