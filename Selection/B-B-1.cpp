#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, b, h; cin >> n >> b >> h;
    vector <vector <vector <int>>> dp(h + 1, vector <vector <int>> (b + h + 1, vector <int> (n + 1)));
    dp[1][b][b] = 1;
    for (int i = 2; i <= h; i++) {
        for (int j = 1; j <= b + h; j++) {
            for (int k = 1; k <= n; k++) {
                if (j - 1 > 0 && k - j >= 0) dp[i][j][k] = (dp[i][j][k] + dp[i - 1][j - 1][k - j]) % mod;
                if (j + 1 <= b + h && k - j >= 0) dp[i][j][k] = (dp[i][j][k] + dp[i - 1][j + 1][k - j]) % mod;
            }
        }
    }
    int sum = 0;
    for (int i = 1; i <= b + h; i++) sum = (sum + dp[h][i][n]) % mod;
    cout << sum;
    return 0;
}