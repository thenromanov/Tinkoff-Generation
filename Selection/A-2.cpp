#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    vector <int64_t> dp(50);
    dp[0] = dp[1] = 1;
    for (int i = 2; i < 50; i++) dp[i] = dp[i - 1] + dp[i - 2];
    int64_t sum = 0;
    for (int i = 0; i < 46; i++) sum += dp[i];
    cout << sum;
    return 0;
}