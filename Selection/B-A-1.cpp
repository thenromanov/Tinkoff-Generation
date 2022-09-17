#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m; cin >> n >> m;
    int64_t cur = 0, x = 0, y = 0;
    vector <int> xs(n), ys(n);
    for (int i = 0; i < n; i++) {
        cin >> xs[i] >> ys[i];
        cur += abs(xs[i]) + abs(ys[i]);
    }
    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());
    string s; cin >> s;
    for (char u : s) {
        int a, r;
        if (u == 'S') {
            a = upper_bound(ys.begin(), ys.end(), y) - ys.begin(), r = n - a;
            y++;
        } else if (u == 'J') {
            r = lower_bound(ys.begin(), ys.end(), y) - ys.begin(), a = n - r;
            y--;
        } else if (u == 'I') {
            a = upper_bound(xs.begin(), xs.end(), x) - xs.begin(), r = n - a;
            x++;
        } else {
            r = lower_bound(xs.begin(), xs.end(), x) - xs.begin(), a = n - r;
            x--;
        }
        cur += a - r;
        cout << cur << '\n';
    }
    return 0;
}