#include <bits/stdc++.h>
using namespace std;

const int maxb = 101;

int bp(int a, int n, int mod) {
    int res = 1;
    while (n) {
        if (n & 1) res = 1LL * res * a % mod;
        a = 1LL * a * a % mod;
        n >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int p; cin >> p;
    vector <int> fac(maxb), inv(maxb);
    fac[0] = 1;
    for (int b = 1; b < p; b += 100) {
        int ans = 0, to = min(p, b + 100);
        for (int i = b; i < to; i++) fac[i - b + 1] = 1LL * fac[i - b] * i % p;
        inv[to - b] = bp(fac[to - b], p - 2, p);
        for (int i = to - 2; i >= b; i--) inv[i - b + 1] = 1LL * inv[i - b + 2] * (i + 1) % p;
        for (int i = b; i < to; i++) ans = (ans + 1LL * fac[i - b] * inv[i - b + 1] % p) % p;
        cout << ans << ' ';
        fac[0] = fac[to - b];
    }
    return 0;
}