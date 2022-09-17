#include <bits/stdc++.h>
using namespace std;

const int maxn = 5007;
vector <int> psum(maxn);
vector <vector <int>> dp(maxn, vector <int> (maxn));
vector <vector <int>> opt(maxn, vector <int> (maxn));

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    while (cin >> n) {
        for (int i = 1; i <= n; i++) cin >> psum[i], psum[i] += psum[i - 1];
        for (int l = 1; l <= n; l++) {
            for (int i = 1; i + l - 1 <= n; i++) {
                dp[i][i + l - 1] = 1e9 + 7;
                if (l == 1) {
                    dp[i][i + l - 1] = 0;
                    opt[i][i + l - 1] = i;
                    continue;
                }
                for (int k = opt[i][i + l - 2]; k <= opt[i + 1][i + l - 1]; k++) {
                    int val = (k - 1 >= i ? dp[i][k - 1] + psum[k - 1] - psum[i - 1] : 0) + (i + l - 1 >= k + 1 ? dp[k + 1][i + l - 1] + psum[i + l - 1] - psum[k] : 0);
                    if (val < dp[i][i + l - 1]) {
                        dp[i][i + l - 1] = val;
                        opt[i][i + l - 1] = k;
                    }
                }
            }
        }
        cout << dp[1][n] << '\n';
    }
    return 0;
}