#include <bits/stdc++.h>
using namespace std;

const int64_t mod = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    vector <int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    int n, k, p; cin >> n >> k >> p;
    if (k == n && p == 1) {
        cout << 1 << '\n';
        return 0;
    }
    vector <int> v(n);
    int64_t ans = 0;
    for (int i = 0; i < n; i++) v[i] = primes[i];
    do {
        set <int64_t> st;
        for (int sz = k; sz <= n; sz++) {
            for (int l = 0; l < n; l++) {
                if (l + sz > n) continue;
                int64_t mul = 1;
                priority_queue <int64_t, vector <int64_t>, greater <int64_t>> mns;
                for (int i = l; i < l + sz; i++) mns.push(v[i]);
                for (int i = 0; i < k; i++) {
                    mul *= mns.top();
                    mns.pop();
                }
                st.insert(mul);
            }
        }
        if (st.size() == p) ans++;
    } while (next_permutation(v.begin(), v.end()));
    cout << ans;
    return 0;
}