#include <bits/stdc++.h>
using namespace std;

const int64_t mod = 1e9 + 9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, d; cin >> n >> d;
    vector <int> v(n);
    for (int& u : v) cin >> u;
    sort(v.begin(), v.end());
    int64_t ans = 1;
    for (int i = 0; i < n; i++) {
        int64_t step = upper_bound(v.begin(), v.end(), v[i] + d) - v.begin() - i;
        ans = (ans * step) % mod;
    }
    cout << ans;
    return 0;
}