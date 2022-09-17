#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n = 10;
    vector <vector <vector <int>>> dp(n, vector <vector <int>> (n, vector <int> (n)));
    dp[1][1][1] = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            for (int k = 1; k < n; k++) {
                if (i == 1 && j == 1 && k == 1) continue;
                bool any = 0;
                for (int p = 1; p <= i / 2; p++) any |= dp[i - p][j][k];
                for (int p = 1; p <= j / 2; p++) any |= dp[i][j - p][k];
                for (int p = 1; p <= k / 2; p++) any |= dp[i][j][k - p];
                if (!any) dp[i][j][k] = 1;
            }
        }
    }
    vector <vector <int>> is_ok(n, vector <int> (n));
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (i == 1 && j == 1) continue;
            bool any = 0;
            for (int p = 1; p <= i / 2; p++) any |= is_ok[i - p][j];
            for (int p = 1; p <= j / 2; p++) any |= is_ok[i][j - p];
            if (!any) is_ok[i][j] = 1;
        }
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            for (int k = 1; k < n; k++) {
                int cur = is_ok[i][j] ^ is_ok[j][k] ^ is_ok[i][k];
                if (cur != dp[i][j][k]) {
                    cout << is_ok[i][j] << ' ' << is_ok[j][k] << ' ' << is_ok[i][k] << '\n';
                    cout << i << ' ' << j << ' ' << k << ' ' << cur << ' ' << dp[i][j][k] << '\n'; 
                }
            }
        }
    }
    return 0;
}