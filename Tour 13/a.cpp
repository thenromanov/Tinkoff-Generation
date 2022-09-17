#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, k; cin >> n >> m;;
    vector <vector <int>> v(n, vector <int> (m));
    for (auto& u : v) {
        for (int& i : u) cin >> i;
    }
    cin >> k;
    vector <pair <int, int>> q(k);
    for (auto& u : q) cin >> u.first >> u.second;
    if (m <= n) {
        for (auto u : q) {
            for (int i = 0; i < m; i++) v[u.first - 1][i] = (v[u.first - 1][i] + v[u.second - 1][i]) % mod;
        }
        for (auto u : v) {
            for (int i : u) cout << i << ' ';
            cout << '\n';
        }
    } else {
        vector <vector <int>> s(n, vector <int> (n));
        for (int i = 0; i < n; i++) s[i][i] = 1;
        for (auto u : q) {
            for (int i = 0; i < n; i++) s[u.first - 1][i] = (s[u.first - 1][i] + s[u.second - 1][i]) % mod;
        }
        vector <vector <int>> ans(n, vector <int> (m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int p = 0; p < n; p++) {
                    ans[i][j] = (ans[i][j] + (1LL * s[i][p] * v[p][j]) % mod) % mod;
                }
            }
        }
        for (auto u : ans) {
            for (int i : u) cout << i << ' ';
            cout << '\n';
        }
    }
    return 0;
}