#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 7;
const int maxk = 21;
const int64_t inf = 1e14 + 179;

struct counter {
    int64_t cost;
    int l, r;
    vector <int> v, cnt;

    counter(vector <int> v) {
        this->v = v;
        cnt.resize(v.size() + 1);
        cost = 0, l = 1, r = 0;
    }

    int64_t get(int lq, int rq) {
        while (r < rq) cost += cnt[v[++r]]++;
        while (l > lq) cost += cnt[v[--l]]++;
        while (rq < r) cost -= --cnt[v[r--]];
        while (lq > l) cost -= --cnt[v[l++]];
        return cost;
    }
};

vector <vector <int64_t>> dp(maxk, vector <int64_t> (maxn, inf));

void calc(int l, int r, int _l, int _r, int k, counter& cost) {
    if (l > r) return;
    int m = (l + r) / 2, opt = _l;
    for (int i = _l; i <= min(m, _r); i++) {
        int64_t val = dp[k - 1][i - 1] + cost.get(i, m);
        if (dp[k][m] > val) {
            dp[k][m] = val;
            opt = i;
        }
    }
    calc(l, m - 1, _l, opt, k, cost);
    calc(m + 1, r, opt, _r, k, cost);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, k; cin >> n >> k;
    vector <int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    counter cost(a);
    dp[0][0] = 0;
    for (int l = 1; l <= k; l++) calc(1, n, 1, n, l, cost);
    cout << dp[k][n] << '\n';
    return 0;
}