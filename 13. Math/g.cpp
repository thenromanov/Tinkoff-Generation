#include <bits/stdc++.h>
using namespace std;

const int maxa = 1.5e7 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    vector <int> v(n), prev(maxa), cnt(maxa);
    vector <pair <int, int>> mn(maxa, {INT_MAX, INT_MAX});
    bool only1 = 1;
    for (int& u : v) cin >> u;
    for (int i = 1; i < n; i++) only1 &= (v[i] == v[0]);
    if (only1) {
        cout << -1 << '\n';
        return 0;
    }
    for (int i = 2; i < maxa; i++) {
        if (!prev[i]) {
            for (int j = i; j < maxa; j += i) prev[j] = i;
        }
    }
    for (int i = 0; i < n; i++) {
        while (v[i] > 1) {
            int cp = prev[v[i]], num = 0;
            while (prev[v[i]] == cp) {
                v[i] /= prev[v[i]];
                num++;
            }
            if (mn[cp].first > num) mn[cp] = {num, 1};
            else if (mn[cp].first == num) mn[cp].second++;
            cnt[cp]++;
        }
    }
    int ans = INT_MAX;
    for (int i = 2; i < maxa; i++) {
        if (prev[i] == i) {
            if (n - cnt[i] > 0) ans = min(ans, n - cnt[i]);
            else ans = min(ans, mn[i].second);
        }
    }
    cout << ans << '\n';
    return 0;
}