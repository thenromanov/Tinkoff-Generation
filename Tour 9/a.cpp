#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m; cin >> n >> m;
    int64_t sum = 0;
    vector <int64_t> deg(n);
    for (int64_t& u : deg) cin >> u, sum += u;
    sort(deg.rbegin(), deg.rend());
    int64_t able = 0;
    for (; able < n; able++) {
        if (able * (able + 1) / 2 > m || deg[able] < able) break;
    }
    for (int64_t ans = able; ans >= 0; ans--) {
        int64_t left = sum - ans * (ans - 1);
        int64_t mdeg = -1;
        if (ans > 0) mdeg = max(mdeg, deg[0] - (ans - 1));
        if (ans < n) mdeg = max(mdeg, deg[ans]);
        if (2 * mdeg >= left && ans * (ans - 1) / 2 + left - mdeg >= m) {
            cout << ans << '\n';
            return 0;
        }
        if (2 * mdeg < left && ans + (ans - 1) / 2 + left / 2 >= m) {
            cout << ans << '\n';
            return 0;
        }
    }
    cout << -1 << '\n';
    return 0;
}