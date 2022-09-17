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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int64_t a, b, c; cin >> a >> b >> c;
    int nd = __gcd(a, b);
    if (c % nd != 0) {
        cout << "Impossible\n";
        return 0;
    }
    a /= nd, b /= nd, c /= nd;
    int64_t x1, y1, d = gcd1(b, a, y1, x1);
    int64_t x0 = x1 * c, y0 = y1 * c;
    if (x0 < 0) {
        int64_t x = ((abs(x0) - 1) / b + 1) * b;
        y0 -= x / b * a;
        x0 += x;
    } else {
        y0 += x0 / b * a;
        x0 %= b;
    }
    cout << x0 << ' ' << y0 << '\n';
    return 0;
}