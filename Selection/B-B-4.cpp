#include <bits/stdc++.h>
using namespace std;

vector <int64_t> compress(vector <int64_t> a) {
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int64_t n1, m1; cin >> n1 >> m1;
    vector <vector <bool>> v1(n1, vector <bool> (m1));
    string s; cin >> s;
    for (int i = 0; i < n1 * m1; i++) v1[i / m1][i % m1] = s[i] - '0';
    int64_t n2, m2; cin >> n2 >> m2;
    vector <vector <bool>> v2(n2, vector <bool> (m2));
    cin >> s;
    for (int i = 0; i < n2 * m2; i++) v2[i / m2][i % m2] = s[i] - '0';
    int64_t a = n1 * n2 / gcd(n1, n2), b = m1 * m2 / gcd(m1, m2);
    int64_t x1 = a / n1, y1 = b / m1, x2 = a / n2, y2 = b / m2;
    vector <int64_t> xs, ys;
    for (int64_t i = 0; i <= n1; i++) xs.push_back(i * x1);
    for (int64_t i = 0; i <= n2; i++) xs.push_back(i * x2);
    for (int64_t i = 0; i <= m1; i++) ys.push_back(i * y1);
    for (int64_t i = 0; i <= m2; i++) ys.push_back(i * y2);
    vector <int64_t> cmpx = compress(xs), cmpy = compress(ys);
    vector <bitset <1000007>> val(cmpx.size());
    for (int64_t i = 0; i < n1; i++) {
        for (int64_t j = 0; j < m1; j++) {
            int lx = lower_bound(cmpx.begin(), cmpx.end(), i * x1) - cmpx.begin(), rx = lower_bound(cmpx.begin(), cmpx.end(), i * x1 + x1) - cmpx.begin();
            int ly = lower_bound(cmpy.begin(), cmpy.end(), j * y1) - cmpy.begin(), ry = lower_bound(cmpy.begin(), cmpy.end(), j * y1 + y1) - cmpy.begin();
            for (int x = lx; x < rx; x++) {
                for (int y = ly; y < ry; y++) val[x][y] = v1[i][j];
            }
        }
    }
    for (int64_t i = 0; i < n2; i++) {
        for (int64_t j = 0; j < m2; j++) {
            int lx = lower_bound(cmpx.begin(), cmpx.end(), i * x2) - cmpx.begin(), rx = lower_bound(cmpx.begin(), cmpx.end(), i * x2 + x2) - cmpx.begin();
            int ly = lower_bound(cmpy.begin(), cmpy.end(), j * y2) - cmpy.begin(), ry = lower_bound(cmpy.begin(), cmpy.end(), j * y2 + y2) - cmpy.begin();
            for (int x = lx; x < rx; x++) {
                for (int y = ly; y < ry; y++) val[x][y] = val[x][y] ^ v2[i][j];
            }
        }
    }
    int64_t ans = 0;
    for (int i = 0; i < cmpx.size() - 1; i++) {
        for (int j = 0; j < cmpy.size() - 1; j++) {
            if (val[i][j] == 0) ans += (cmpx[i + 1] - cmpx[i]) * (cmpy[j + 1] - cmpy[j]);
        }
    }
    cout << ans;
    return 0;
}