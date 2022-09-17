#include <bits/stdc++.h>
using namespace std;

const double inf = 1e20 + 179;

double dist(pair <int, int> c1, pair <int, int> c2) {
    return sqrt(1.0 * (c1.first - c2.first) * (c1.first - c2.first) + 1.0 * (c1.second - c2.second) * (c1.second - c2.second));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    vector <pair <int, int>> coords(n);
    for (auto& u : coords) cin >> u.first >> u.second;
    vector <int> l(n, -1), r(n, -1);
    stack <int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && coords[i].second > coords[st.top()].second) {
            r[st.top()] = i;
            st.pop();
        }
        if (!st.empty()) {
            l[i] = st.top();
            if (coords[i].second == coords[st.top()].second) {
                r[st.top()] = i;
                st.pop();
            }
        }
        st.push(i);
    }
    vector <double> dp(n, inf);
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        if (l[i] != -1) dp[i] = min(dp[i], max(dp[l[i]], dist(coords[l[i]], coords[i])));
        if (r[i] != -1) dp[r[i]] = min(dp[r[i]], max(dp[i], dist(coords[i], coords[r[i]])));
    }
    cout << fixed << setprecision(10) << dp[n - 1];
    return 0;
}