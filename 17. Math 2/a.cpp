#include <bits/stdc++.h>
using namespace std;

const int64_t mod = 998244353;

int64_t bp(int64_t a, int64_t n) {
    int64_t res = 1;
    while (n) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    vector <int> v(n);
    for (int& u : v) cin >> u;
    int64_t sum = 0, cur = 1, pwr = 1;
    for (int i = 0; i < n; i++) {
        sum = (sum + cur * bp(pwr, mod - 2) % mod) % mod;
        pwr = pwr * 100 % mod;
        cur = cur * v[i] % mod;
    }
    sum = sum * bp(cur * bp(pwr, mod - 2) % mod, mod - 2) % mod;
    cout << sum << '\n';
    return 0;
}