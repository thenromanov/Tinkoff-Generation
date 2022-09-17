#include <bits/stdc++.h>
using namespace std;

int64_t to_mask(vector <vector <int>>& a) {
    int64_t b = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            b = (b << 6) + a[i][j];
        }
    }
    return b;
}

vector <vector <int>> to_arr(int64_t mask) {
    vector <vector <int>> v(3, vector <int>(3));
    for (int i = 2; i >= 0; i--) {
        for (int j = 2; j >= 0; j--) {
            v[i][j] = mask & 63;
            mask >>= 6;
        }
    }
    return v;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, q; cin >> n >> q;
    vector <int> b(n), e(n);
    for (int& u : b) cin >> u;
    for (int& u : e) cin >> u;
    vector <vector <int>> c(3, vector <int> (3));
    for (int i = 0; i < n; i++) c[b[i] - 1][e[i] - 1]++;
    vector <int64_t> masks = {to_mask(c)};
    for (int i = 0; i < q; i++) {
        int b, e; cin >> b >> e; b--, e--;
        vector <int64_t> new_masks;
        for (auto mask : masks) {
            vector <vector <int>> cur = to_arr(mask);
            for (int i = 0; i < 3; i++) {
                if (cur[b][i] == 0) continue;
                cur[b][i]--;
                cur[e][i]++;
                new_masks.push_back(to_mask(cur));
                cur[e][i]--;
                cur[b][i]++;
            }
        }
        masks = new_masks;
        sort(masks.begin(), masks.end());
        masks.erase(unique(masks.begin(), masks.end()), masks.end());
    }
    for (auto mask : masks) {
        vector <vector <int>> cur = to_arr(mask);
        int s = 0;
        for (int i = 0; i < 3; i++) s += cur[i][i];
        if (s == n) {
            cout << "YES\n";
            return 0;
        }
    }
    cout << "NO\n";
    return 0;
}