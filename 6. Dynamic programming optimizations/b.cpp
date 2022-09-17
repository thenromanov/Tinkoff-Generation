#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e4 + 179;
const int maxk = 179;
const double inf = 1e16 + 179;

vector <int64_t> psum(maxn), psum2(maxn);
vector <vector <double>> dp(maxk, vector <double> (maxn, inf));

double cost(int l, int r) {
    return (double)(psum2[r] - psum2[l - 1]) - (double)(psum[r] - psum[l - 1]) * (double)(psum[r] - psum[l - 1]) / (double)(r - l + 1);
}

void calc(int l, int r, int _l, int _r, int k) {
    if (l > r) return;
    int m = (l + r) / 2, opt = _l;
    for (int i = _l; i <= min(m, _r); i++) {
        double val = dp[k - 1][i - 1] + cost(i, m);
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
    int n, k; cin >> n >> k;
    vector <int64_t> stations(n);
    for (int64_t& u : stations) cin >> u;
    sort(stations.begin(), stations.end());
    for (int i = 0; i < n; i++) {
        psum[i + 1] = psum[i] + stations[i];
        psum2[i + 1] = psum2[i] + stations[i] * stations[i];
    }
    dp[0][0] = 0;
    for (int l = 1; l <= k; l++) calc(1, n, 1, n, l);
    cout << fixed << setprecision(10) << dp[k][n];
    return 0;
}