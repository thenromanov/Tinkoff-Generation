#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, q; cin >> n >> q;
    vector <int> v(n);
    for (int& u : v) cin >> u;
    sort(v.rbegin(), v.rend());
    vector <int> cnt(n + 1);
    for (int i = 0, l, r; i < q; i++) {
        cin >> l >> r; l--, r--;
        cnt[l]++, cnt[r + 1]--;
    }
    vector <int> num(n);
    int s = 0;
    for (int i = 0; i < n; i++) {
        s += cnt[i];
        num[i] = s;
    }
    sort(num.rbegin(), num.rend());
    int64_t sum = 0;
    for (int i = 0; i < n; i++) sum += 1LL * num[i] * v[i];
    cout << sum << '\n';
    return 0;
}