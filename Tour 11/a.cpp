#include <bits/stdc++.h>
using namespace std;

const int64_t k = 1e5 + 179;
const int64_t mod = 1e9 + 9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    vector <int64_t> a(n), b(n);
    for (int64_t& u : a) cin >> u;
    for (int64_t& u : b) cin >> u;
    vector <int64_t> phasha(n + 1), shasha(n + 1), phashb(n + 1), pwr(n + 1);
    pwr[0] = 1; for (int i = 1; i <= n; i++) pwr[i] = (pwr[i - 1] * k) % mod;
    for (int i = 0; i < n; i++) phasha[i + 1] = (phasha[i] * k + a[i]) % mod;
    for (int i = n; i > 0; i--) shasha[i - 1] = (shasha[i] * k + a[i - 1]) % mod;
    for (int i = 0; i < n; i++) phashb[i + 1] = (phashb[i] * k + b[i]) % mod;
    vector <int> ans;
    for (int i = 1; i <= n; i++) {
        int64_t pref = (phasha[n] - phasha[i - 1] * pwr[n - i + 1] % mod + mod) % mod, suff;
        if ((n - i + 1) % 2 == 0) suff = phasha[i - 1];
        else suff = (shasha[0] - shasha[i - 1] * pwr[i - 1] % mod + mod) % mod;
        if (pref == phashb[n - i + 1] && suff == (phashb[n] - phashb[n - i + 1] * pwr[i - 1] % mod + mod) % mod) ans.push_back(i);
    }
    cout << (int)ans.size() << '\n';
    for (int u : ans) cout << u << ' ';
    return 0;
}