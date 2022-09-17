#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int64_t x, n, m, w, t; cin >> x >> n >> m >> w >> t;
    vector <int64_t> st(n);
    for (int64_t& u : st) cin >> u;
    vector <pair <int64_t, int64_t>> pers(m);
    for (auto& u : pers) cin >> u.first >> u.second;
    int64_t ans = LLONG_MAX;
    for (int k = 0; k < (1 << m); k++) {
        int64_t cur = w;
        for (int64_t t)
        ans = min(ans, cur);
    }
    cout << ans << '\n';
    return 0;
}