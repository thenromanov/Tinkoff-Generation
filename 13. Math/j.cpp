#include <bits/stdc++.h>
using namespace std;

int64_t gcd1(int64_t a, int64_t b, int64_t& x, int64_t& y) {
    if (a == 0) {
        x = 0, y = 1;
        return b;
    }
    int64_t x1, y1, d = gcd1(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

void solve() {
    int64_t p, q, a, b, k1, k2; cin >> p >> q >> a >> b;
    p = (((abs(p) - 1) / a + 1) * a + p) % a;
    q = (((abs(q) - 1) / b + 1) * b + q) % b;
    int64_t nd = __gcd(a, b);
    int64_t lcm = a * b / nd;
    if ((p - q) % nd != 0) {
        cout << "NO\n";
        return;
    }
    a /= nd, b /= nd;
    int64_t c = p - q;
    int64_t x1, y1, d = gcd1(a, b, x1, y1);
    k1 = -x1 * c, k2 = y1 * c;
    cout << "YES ";
    int64_t ans = k1 * a + p;
    int64_t ans1 = (10000000LL * lcm + ans) % lcm;
    assert(ans1 >= 0);
    cout << ans1 << ' ' << lcm << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}