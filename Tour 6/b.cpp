#include <bits/stdc++.h>
using namespace std;

const int maxn = 2179;
const int inf = 1e7;

int n, m;

vector <vector <int>> psum(maxn, vector <int> (maxn));
int get_sum(int lx, int ly, int rx, int ry) {
    if (lx < 1) return inf;
    if (ly < 1) return inf;
    if (rx > n) return inf;
    if (ry > m) return inf;
    return psum[rx][ry] - psum[rx][ly - 1] - psum[lx - 1][ry] + psum[lx - 1][ly - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < m; j++) {
            psum[i + 1][j + 1] = psum[i][j + 1] + psum[i + 1][j] - psum[i][j] + (s[j] == '#');
        }
    }
    int l = 1, r = maxn;
    while (l + 1 < r) {
        int k = (l + r) / 2;
        bool ok = false;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                int sum = get_sum(i - k, j, i - 1, j + k - 1) + get_sum(i, j - k, i + k - 1, j - 1) + get_sum(i, j, i + k - 1, j + k - 1) + get_sum(i, j + k, i + k - 1, j + 2 * k - 1) + get_sum(i + k, j, i + 2 * k - 1, j + k - 1);
                if (sum == k * k * 5) ok = true;
            }
        }
        if (ok) l = k;
        else r = k;
    }
    cout << l << '\n';
    return 0;
}