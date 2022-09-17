#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    set <pair <pair <int, int>, int>> used;
    map <pair <pair <int, int>, int>, int64_t> eq;
    map <pair <int, int>, int64_t> ks;
    int64_t sum = 0;
    for (int i = 0, t, a, b, c; i < n; i++) {
        cin >> t >> a >> b >> c;
        if (a < 0 || (a == 0 && b < 0)) a = -a, b = -b, c = -c;
        if (t == 1) {
            int64_t q; cin >> q;
            int gcdab = __gcd(abs(a), abs(b));
            int allgcd = __gcd(abs(gcdab), abs(c));
            used.insert({{a / allgcd, b / allgcd}, c / allgcd});
            eq[{{a / allgcd, b / allgcd}, c / allgcd}] += q;
            a /= gcdab, b /= gcdab;
            ks[{a, b}] += q;
            sum += q;
        } else {
            int gcdab = __gcd(abs(a), abs(b));
            int allgcd = __gcd(abs(gcdab), abs(c));
            if (used.find({{a / allgcd, b / allgcd}, c / allgcd}) != used.end()) {
                if (eq[{{a / allgcd, b / allgcd}, c / allgcd}] == 0) cout << sum - ks[{a, b}] << '\n';
                else cout << "inf\n";
            } else {
                a /= gcdab, b /= gcdab;
                cout << sum - ks[{a, b}] << '\n';
            }
        }
    }
    return 0;
}