#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    vector <int> v(n), r(n, n), l(n, -1), rbits(n, n), lbits(n, -1);
    for (int& u : v) cin >> u;
    stack <int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && v[i] > v[st.top()]) {
            r[st.top()] = i;
            st.pop();
        }
        if (!st.empty()) l[i] = st.top();
        st.push(i);
    }
    vector <int> bits(30, -1);
    for (int i = n - 1; i >= 0; i--) {
        for (int b = 0; b < 30; b++) {
            if ((((v[i] >> b) & 1) == 0) && bits[b] != -1) {
                rbits[i] = min(rbits[i], bits[b]);
            }
            if ((v[i] >> b) & 1) bits[b] = i;
        }
    }
    bits.assign(30, -1);
    for (int i = 0; i < n; i++) {
        for (int b = 0; b < 30; b++) {
            if ((((v[i] >> b) & 1) == 0) && bits[b] != -1) {
                lbits[i] = max(lbits[i], bits[b]);
            }
            if ((v[i] >> b) & 1) bits[b] = i;
        }
    }
    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        lbits[i] = max(lbits[i], l[i]);
        rbits[i] = min(rbits[i], r[i]);
        ans += (int64_t)(i - l[i]) * (r[i] - i) - (int64_t)(i - lbits[i]) * (rbits[i] - i);
    }
    cout << ans;
    return 0;
}