#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    vector <pair <int, int>> v(n);
    for (auto& u : v) cin >> u.first >> u.second;
    int s; cin >> s;
    for (int i = 0; i < n; i++) {
        int x = v[i].first, y = v[i].second * s;
        v[i].first = - x - y, v[i].second = x - y;
    }
    v.push_back({0, 0}); n++;
    sort(v.begin(), v.end());
    vector <int> a(n);
    for (int i = 0; i < n; i++) a[i] = v[i].second;
    vector <int> d(n + 1, INT_MAX);
    int ans = 0, len = 0;
    d[0] = INT_MIN;
    for (int i = 0; i < n; i++) {
        int j = int(upper_bound(d.begin(), d.end(), a[i]) - d.begin());
        if (v[i] == make_pair(0, 0)) ans = j;
        else if (d[j - 1] <= a[i] && a[i] < d[j]) {
            d[j] = a[i], len = max(len, j);
        }
    }
    cout << ans - 1 << ' ' << len << '\n';
    return 0;
}