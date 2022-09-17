#include <bits/stdc++.h>
using namespace std;

const int K = 300;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m; cin >> n >> m;
    vector <int> a(n), next(n), cnt(n), lastin(n);
    for (int& u : a) cin >> u;
    for (int block = 0; block < (n - 1) / K + 1; block++) {
        int r = min(block * K + K - 1, n - 1);
        for (int i = r; i >= block * K; i--) {
            if (i + a[i] > r) {
                next[i] = i + a[i];
                lastin[i] = i;
                cnt[i] = 1;
            } else {
                next[i] = next[i + a[i]];
                lastin[i] = lastin[i + a[i]];
                cnt[i] = cnt[i + a[i]] + 1;
            }
        }
    }
    while (m--) {
        int c, x, y; cin >> c;
        if (c == 0) {
            cin >> x >> y; x--;
            int block = x / K, r = min(block * K + K - 1, n - 1);
            if (x + y > r) {
                next[x] = x + y;
                lastin[x] = x;
                cnt[x] = 1;
            } else {
                next[x] = next[x + y];
                lastin[x] = lastin[x + y];
                cnt[x] = cnt[x + y] + 1;
            }
            a[x] = y;
            for (int i = x - 1; i >= block * K; i--) {
                if (i + a[i] > r) {
                    next[i] = i + a[i];
                    lastin[i] = i;
                    cnt[i] = 1;
                } else {
                    next[i] = next[i + a[i]];
                    lastin[i] = lastin[i + a[i]];
                    cnt[i] = cnt[i + a[i]] + 1;
                }
            }
        } else {
            cin >> x; x--;
            int ans = 0, last = x;
            while (x < n) {
                ans += cnt[x];
                last = x;
                x = next[x];
            } 
            cout << lastin[last] + 1 << ' ' << ans << '\n';
        }
    }
    return 0;
}