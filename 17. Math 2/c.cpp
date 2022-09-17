#include <bits/stdc++.h>
using namespace std;

const int maxn = 40;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    vector <vector <int64_t>> dp(maxn, vector <int64_t> (maxn));
    dp[0][0] = 1;
    for (int i = 1; i < maxn; i++) {
        for (int j = 0; j < maxn; j++) dp[i][j] = (j - 1 >= 0 ? dp[i - 1][j - 1] : 0) + (j + 1 < maxn ? dp[i - 1][j + 1] : 0);
    }
    int n;
    int64_t k, d = 0; cin >> n >> k;
    for (int i = 0; i < 2 * n; i++) {
        if (dp[2 * n - (i + 1)][d + 1] >= k) cout << '(', d++;
        else k -= dp[2 * n - (i + 1)][d + 1], cout << ')', d--;
    }
    return 0;
}