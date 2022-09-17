#include <bits/stdc++.h>
using namespace std;

const int64_t mod = 738832927927;

mt19937 gena;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    map <int, int64_t> num;
    int n; cin >> n;
    vector <set <int64_t>> exists(n);
    vector <int> v(n);
    for (int& u : v) cin >> u;
    for (int i = 0; i < n; i++) {
        int64_t cur = 0;
        for (int j = i; j < n; j++) {
            if (num.find(v[j]) == num.end()) num[v[j]] = gena();
            cur = (cur + num[v[j]]) % mod;
            exists[j - i].insert(cur);
        }
    }
    int m, ans = 0; cin >> m;
    vector <int> a(m);
    for (int& u : a) cin >> u;
    for (int i = 0; i < m; i++) {
        int64_t cur = 0;
        for (int j = i; j < m; j++) {
            if (j - i >= n || num.find(a[j]) == num.end()) break;
            cur = (cur + num[a[j]]) % mod;
            if (exists[j - i].find(cur) != exists[j - i].end()) ans = max(ans, j - i + 1);
        }
    }
    cout << ans << '\n';
    return 0;
}