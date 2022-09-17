#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 179;
const int maxk = 179;
const int64_t inf = 1e14 + 179;

vector <int64_t> d(maxn, inf), psum(maxn);
vector <vector <int64_t>> dp(maxk, vector <int64_t> (maxn, inf));

int64_t cost(int l, int r) {
    return d[r] * (r - l + 1) - psum[r] + psum[l - 1];
}

void calc(int l, int r, int _l, int _r, int k) {
    if (l > r) return;
    int m = (l + r) / 2, opt = _l;
    for (int i = _l; i <= min(m, _r); i++) {
        int64_t val = dp[k - 1][i - 1] + cost(i, m);
        if (dp[k][m] > val) {
            dp[k][m] = val;
            opt = i;
        }
    }
    calc(l, m - 1, _l, opt, k);
    calc(m + 1, r, opt, _r, k);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, p; cin >> n >> m >> p;
    vector <int64_t> pdist(n);
    for (int i = 1; i < n; i++) cin >> pdist[i], pdist[i] += pdist[i - 1];
    d[0] = -inf;
    for (int i = 1, t, h; i <= m; i++) {
        cin >> h >> t;
        d[i] = t - pdist[h - 1];
    }
    sort(d.begin(), d.end());
    for (int i = 0; i < m; i++) psum[i + 1] = psum[i] + d[i + 1];
    dp[0][0] = 0;
    for (int l = 1; l <= p; l++) calc(1, m, 1, m, l);
    cout << dp[p][m] << '\n';
    return 0;
}