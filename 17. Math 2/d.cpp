#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    double p; int n, t; cin >> n >> p >> t;
    vector <vector <double>> dp(t + 1, vector <double> (n + 1));
    dp[0][0] = 1;
    for (int i = 0; i < t; i++) {
        for (int j = 0; j <= n; j++) {
            if (j == n) dp[i + 1][j] += dp[i][j];
            else {
                dp[i + 1][j] += dp[i][j] * (1 - p);
                dp[i + 1][j + 1] += dp[i][j] * p;
            }
        }
    }
    double ans = 0;
    for (int j = 0; j <= n; j++) ans += dp[t][j] * j;
    cout << fixed << setprecision(10) << ans << '\n';
    return 0;
}