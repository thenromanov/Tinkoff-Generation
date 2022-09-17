#include <bits/stdc++.h>
using namespace std;

int n;
vector <vector <int>> bad;
vector <int> used;

int64_t get_ans(int v, int i) {
    if (i == n - 1) return 1;
    int64_t ans = 0;
    used[v] = 1;
    for (int j = 0; j < n; j++) {
        if (!used[j] && !bad[v][j]) {
            ans += get_ans(j, i + 1);
        }
    }
    used[v] = 0;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n;
    bad.resize(n, vector <int> (n));
    used.resize(n);
    for (int i = 0, v, u; i < n - 1; i++) {
        cin >> v >> u; v--, u--;
        bad[v][u] = 1;
        bad[u][v] = 1;
    }
    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        ans += get_ans(i, 0);
    }
    cout << ans << "\n";
    return 0;
}