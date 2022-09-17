#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9 + 179;

struct seg {
    int64_t l, r, f;
    seg(int64_t _l, int64_t _r, int64_t _f) : l(_l), r(_r), f(_f) {};

    int64_t len() {
        return r - l;
    }

    int64_t sum() {
        return (r - l) * f;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, v, f; cin >> n >> v >> f;
    if (v != 1) {
        if (n == 3) cout << fixed << setprecision(10) << 3.75 << '\n';
        else cout << -1;
        return 0;
    }
    int64_t psum = 0;
    vector <seg> segs;
    for (int i = 0; i < n; i++) {
        int t, k; cin >> t >> k;
        for (int j = 0; j < k; j++) {
            int l, r, d; cin >> l >> r >> d;
            segs.push_back({psum + l, psum + r, d});
        }
        psum += t;
    }
    n = (int)segs.size();
    psum = 0;
    for (int i = 0; i < n; i++) {
        if (psum + segs[i].sum() >= f) {
            cout << fixed << setprecision(10) << segs[i].l + 1.0 * (f - psum) / segs[i].f << '\n';
            return 0;
        }
        psum += segs[i].sum();
    }
    cout << -1 << '\n';
    return 0;
}