#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int len = 16;
    int64_t all = 1, ans = 0;
    for (int i = 0; i < len; i++) all *= 3;
    for (int i = 0; i < all; i++) {
        vector <int> v(len);
        int cp = i;
        for (int pos = len - 1; pos >= 0; pos--) {
            v[pos] = cp % 3;
            cp /= 3;
        }
        set <int> used;
        for (int i = 0; i < len; i++) used.insert(v[i]);
        if (used.size() == 3 && v[0] != v[1] && v[1] != v[2] && v[2] != v[3] && v[3] != v[4] && v[4] != v[5] && v[5] != v[6] && v[6] != v[7] && v[7] != v[8] && v[8] != v[9]) ans++;
    }
    cout << ans;
    return 0;
}