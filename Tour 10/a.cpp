#include <bits/stdc++.h>
using namespace std;

vector <int64_t> solve(vector <int>& v, int l, int r) {
    int mn = INT_MAX;
    for (int i = l; i <= r; i++) mn = min(mn, v[i]);
    vector <int64_t> res(r - l + 2, LLONG_MAX);
    int cnt = 0;
    for (int i = l; i <= r; i++) {
        v[i] -= mn;
        cnt += (v[i] == 0);
    }
    res[cnt] = mn;
    int cur = cnt;
    for (int i = l; i <= r; i++) {
        if (v[i] == 0) continue;
        int j = i;
        while (j + 1 <= r && v[j + 1] != 0) j++;
        vector <int64_t> subres = solve(v, i, j);
        for (int k1 = cur; k1 >= cnt; k1--) {
            for (int k2 = 0; k2 <= j - i + 1; k2++) {
                if (res[k1] != LLONG_MAX && subres[k2] != LLONG_MAX) res[k1 + k2] = min(res[k1 + k2], res[k1] + subres[k2]);
            }
        }
        cur += j - i + 1;
        i = j;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, k; cin >> n >> k;
    vector <int> v(n);
    for (int& u : v) cin >> u;
    vector <int64_t> res = solve(v, 0, n - 1);
    int ans = 0;
    for (int i = n; i >= 0; i--) {
        if (res[i] <= k) {
            ans = i;
            break;
        }
    }
    cout << ans << '\n';
    return 0;
}