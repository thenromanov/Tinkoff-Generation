#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, ans = 0; cin >> n;
    for (int i = 0, l; i < n; i++) {
        cin >> l;
        vector <int> v(l);
        for (int& u : v) cin >> u;
        sort(v.begin(), v.end());
        for (int i = 1; i < l; i++) ans = max(ans, v[i] - v[i - 1]);
    }
    cout << ans << '\n';
    return 0;
}