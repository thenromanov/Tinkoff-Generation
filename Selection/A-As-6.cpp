#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, k; cin >> n >> m >> k;
    vector <vector <int>> c(k, vector <int> (3));
    for (int i = 0; i < k; i++) {
        cin >> c[i][0] >> c[i][1] >> c[i][2];
        c[i][0]--, c[i][1]--;
    }
    int64_t ans = 0, cur = 0;
    for (int i = 0; i < n; i++) {
        cur = 0;
        vector <vector <int64_t>> line;
        int lastx = 0;
        line.push_back({m, 1, k});
        for (int j = 0; j < k; j++) {
            int64_t x = c[j][0], y = c[j][1], r = c[j][2], pos = abs(x - i);
            if (pos <= r) {
                int64_t lb = r >= pos ? sqrt(r * r - pos * pos) : 0;
                line.push_back({y - lb, -1, k - 1 - j});
                line.push_back({y + lb + 1, 1, k - 1 - j});
            }
        }
        sort(line.begin(), line.end());
        set <int> st; st.insert(k);
        for (auto u : line) {
            cur += (u[0] - lastx) * (*st.begin());
            lastx = u[0];
            if (u[1] == -1) st.insert(u[2]);
            else st.erase(u[2]);
        }
        ans += cur;
    }
    cout << ans;
    return 0;
}