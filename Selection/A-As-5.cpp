#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m; cin >> n >> m;
    vector <vector <bitset <50001>>> cnt(m, vector <bitset <50001>> (26));
    vector <string> v(n);
    for (string& u : v) cin >> u;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (v[i][j] == '?') for (int k = 0; k < 26; k++) cnt[j][k][i] = 1;
            else cnt[j][v[i][j] - 'a'][i] = 1;
        }
    }
    bitset <50001> s = 0;
    for (int i = 0; i < n; i++) s[i] = 1;
    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        bitset <50001> b = s;
        for (int j = 0; j < m; j++) {
            bitset <50001> add = 0;
            if (v[i][j] == '?') {
                for (int k = 0; k < 26; k++) add |= cnt[j][k];
                b &= add;
            } else {
                b &= cnt[j][v[i][j] - 'a'];
            }
        }
        int64_t cnt = b.count();
        ans += cnt - 1;
    }
    cout << ans / 2;
    return 0;
}