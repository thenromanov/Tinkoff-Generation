#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 7;

int64_t bp(int64_t a, int64_t n, int64_t mod) {
    int64_t res = 1;
    while (n) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

int64_t C(int64_t n, int64_t k, int64_t mod) {
    if (k > n || n < 0) return 0;
    int64_t res = 1, cnt1 = 0, cnt2 = 0;
    for (int64_t i = n; i > n - k; i--) {
        int64_t cp = i;
        while (cp && cp % mod == 0) cnt1++, cp /= mod;
        res = res * cp % mod;
        cp = i - n + k;
        while (cp && cp % mod == 0) cnt2++, cp /= mod;
        res = res * bp(cp, mod - 2, mod) % mod;
    }
    if (cnt1 > cnt2) return 0;
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int64_t n, k, m; cin >> n >> k >> m;
    cout << C(n - k + 1, k, m) << '\n';
    return 0;
}