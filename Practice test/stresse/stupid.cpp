#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, q; cin >> n >> q;
    vector <int64_t> v(n);
    for (auto& u : v) cin >> u;
    for (int i = 0, c, l, r; i < q; i++) {
        cin >> c >> l >> r; l--, r--;
        if (c == 0) {
            int64_t ans = 0;
            for (int i = l; i <= r; i++) ans = gcd(ans, v[i]);
            cout << ans << '\n';
        } else {
            int64_t k, cur; cin >> k; cur = k;
            for (int i = l; i <= r; i++) v[i] += cur, cur += k; 
        }
    }
    return 0;
}