#include <bits/stdc++.h>
using namespace std;

mt19937 gena(time(0));

const int64_t mod = 738832927927;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string s; cin >> s;
    int n = (int)s.size();
    vector <int> v(n), mp(26, INT_MIN);
    for (int i = 0; i < n; i++) {
        int c = s[i] - 'a';
        if (mp[c] == INT_MIN) mp[c] = gena();
        v[i] = mp[c];
    }
    vector <int64_t> pref(n + 1);
    for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + v[i];
    int res = 1;
    for (int x = 1; x * x <= n; x++) {
        if (n % x == 0) {
            int64_t ans = pref[x];
            int mb = n / x, step = x;
            for (int i = 2 * step; i <= n; i += step) {
                int64_t cur = pref[i] - pref[i - step];
                if (cur != ans) {
                    mb = 0;
                    break;
                }
            }
            res = max(res, mb);
            ans = pref[n / x], mb = x, step = n / x;
            for (int i = 2 * step; i <= n; i += step) {
                int64_t cur = pref[i] - pref[i - step];
                if (cur != ans) {
                    mb = 0;
                    break;
                }
            }
            res = max(res, mb);
        }
    }
    cout << res << '\n';
    return 0;
}