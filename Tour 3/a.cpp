#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    vector <int> v(n);
    for (int& u : v) cin >> u;
    sort(v.begin(), v.end());
    int ans = INT_MAX;
    for (int i = 0; i < n; i++) {
        int r = v[i] + n - 1;
        int cnt = upper_bound(v.begin(), v.end(), r) - v.begin();
        int need = i + n - cnt;
        ans = min(ans, need);
    }
    cout << ans;
    return 0;
}