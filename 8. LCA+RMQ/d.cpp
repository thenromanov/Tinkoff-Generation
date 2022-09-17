#include <bits/stdc++.h>
using namespace std;

const int64_t cost = 1e9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, a; cin >> n >> a;
    vector <int64_t> l(n), r(n), c(n), dp(a + 1);
    vector <int> last(n);
    vector <deque <int>> q(n);
    for (int i = 0; i < n; i++) cin >> l[i] >> r[i] >> c[i], last[i] = a;
    for (int i = a; i >= 0; i--) {
        dp[i] = cost * i;
        for (int j = 0; j < n; j++) {
            if (i + l[j] <= a) {
                while (!q[j].empty() && dp[q[j].back()] >= dp[i + l[j]]) q[j].pop_back();
                q[j].push_back(i + l[j]);
            }
            if (i + r[j] < a) {
                if (q[j].front() == last[j]--) q[j].pop_front();
            }
        }
        for (int j = 0; j < n; j++) {
            if (i + r[j] > a) continue;
            int64_t mv = dp[q[j].front()];
            mv -= c[j];
            dp[i] = max(dp[i], mv);
        }
    }
    cout << dp[0] << '\n';
    return 0;
}