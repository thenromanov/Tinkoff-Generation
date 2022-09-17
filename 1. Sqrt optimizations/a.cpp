#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int x; cin >> x;
    vector <pair <int, int>> ans;
    int i = 1;
    for (; i * i <= 2 * x; i++) {
        if ((x + i - 1) % (2 * i + 1) == 0) {
            int j = (x + i - 1) / (2 * i + 1);
            if (i <= j) ans.push_back({j, i});
        }
        if ((x + i) % (2 * i + 1) == 0) {
            int j = (x + i) / (2 * i + 1);
            if (i < j) ans.push_back({i, j});
        }
    }
    cout << ans.size() << '\n';
    for (auto u : ans) cout << u.first << ' ' << u.second << '\n';
    return 0;
}