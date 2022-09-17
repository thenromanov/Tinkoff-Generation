#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    vector <vector <int>> pper(n + 1, vector <int> (m)), rep(n + 1, vector <int> (m));
    for (int j = 0; j < m; j++) pper[0][j] = rep[0][j] = j;
    for (int i = 1; i <= n; i++) {
        vector <int> cur(m);
        for (int& u : cur) cin >> u, u--;
        for (int j = 0; j < m; j++) pper[i][j] = cur[pper[i - 1][j]];
        for (int j = 0; j < m; j++) rep[i][pper[i][j]] = j;
    }
    map <pair <int, int>, int64_t> ans;
    int q; cin >> q;
    for (int i = 0, l, r; i < q; i++) {
        cin >> l >> r;
        if (ans.find({l, r}) != ans.end()) {
            cout << ans[{l, r}] << '\n';
            continue;
        }
        int64_t res = 0;
        for (int j = 0; j < m; j++) res += (1LL + pper[r][rep[l - 1][j]]) * (1LL + j);
        ans[{l, r}] = res;
        cout << res << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int q; cin >> q;
    while (q--) solve();
    return 0;
}