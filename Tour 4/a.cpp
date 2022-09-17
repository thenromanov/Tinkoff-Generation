#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    vector <int64_t> psum(n), ssum(n);
    for (int i = 0, v; i < n; i++) {
        cin >> v;
        psum[i] = v;
        ssum[i] = v;
    }
    for (int i = 1; i < n; i++) psum[i] += psum[i - 1];
    for (int i = n - 2; i >= 0; i--) ssum[i] += ssum[i + 1];
    int ans = n - 1;
    int l = 0, r = n - 1, lastl = -1, lastr = n, cnt = 0;
    while (r > l) {
        while (ssum[r] < psum[l]) r--;
        if (l >= r) break;
        if (psum[l] == ssum[r]) {
            cnt += (l - lastl - 1) + (lastr - r - 1);
            lastl = l;
            lastr = r;
            ans = min(ans, cnt + max(r - l - 2, 0));
        }
        l++;
    }
    cout << ans << '\n';
    return 0;
}