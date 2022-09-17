#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    vector <int> v(n);
    for (auto& u : v) cin >> u;
    int curmax = 0;
    int64_t ans = 0;
    for (int i = 0; i < (1 << n); i++) {
        vector <int> cur;
        for (int j = n - 1; j >= 0; j--) {
            if (((i >> j) & 1) == 0) cur.push_back(v[j]);
        }
        for (int j = 0; j < n; j++) {
            if (((i >> j) & 1)) cur.push_back(v[j]);
        }
        for (auto u : cur) cout << u << ' ';
        vector <pair <int, int>> dp(n, {1, 1});
        for (int j = 1; j < n; j++) {
            for (int k = j - 1; k >= 0; k--) {
                if (cur[k] > cur[j]) {
                    if (dp[k].first + 1 > dp[j].first) dp[j] = {dp[k].first + 1, dp[k].second};
                    else if (dp[k].first + 1 == dp[j].first) dp[j].second += dp[k].second;
                }
            }
        }
        int mx = 0;
        for (auto u : dp) mx = max(mx, u.first);
        cout << mx << '\n';
        if (mx < curmax) continue;
        if (mx > curmax) ans = 0;
        curmax = mx;
        for (auto u : dp) if (u.first == mx) ans += u.second;
    }
    cout << curmax << ' ' << ans / 2 << '\n';
    return 0;
}