#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int64_t k, ans = LLONG_MAX; cin >> k;
    for (int64_t i = 1; i * i <= k; i++) {
        if (k % i == 0) {
            int64_t j = k / i;
            ans = min(ans, i + j - 2);
        }
    }
    cout << ans;
    return 0;
}