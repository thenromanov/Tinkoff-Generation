#include <bits/stdc++.h>
using namespace std;

const int maxn = 41;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    vector <vector <int64_t>> dp(maxn, vector <int64_t> (10));
    for (int i = 1; i <= 9; i++) dp[0][i] = 1;
    for (int i = 1; i < maxn; i++) {
        for (int j = 0; j <= 9; j++) {
            for (int k = j; k <= 9; k++) dp[i][j] += dp[i - 1][k];
        }
    }
    int n; cin >> n;
    for (int i = maxn - 1; i >= 0; i--) {
        int64_t sum = dp[i][0];
        for (int j = 1; j <= 9; j++) {
            if (sum < n && sum + dp[i][j] >= n) {
                cout << j;
                for (int k = 1; k <= j; k++) n -= dp[i][k];
                break;
            }
            sum += dp[i][j];
        }
    }
    return 0;
}