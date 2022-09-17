#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int64_t n; cin >> n;
    vector <int> prime(n + 2, 1);
    vector <int> cnt(n + 1, 1);
    prime[0] = prime[1] = 0;
    for (int64_t i = 2; i <= n + 1; i++) {
        if (prime[i]) {
            if (i * i <= n + 1) for (int j = i * i; j <= n + 1; j += i) prime[j] = 0;
            for (int64_t j = n * n / i * i; j <= n * n + n; j += i) if (j - n * n >= 0) cnt[j - n * n] = 0;
        }
    }
    int ans = 0;
    for (int u : cnt) ans += u;
    cout << ans << '\n';
    return 0;
}