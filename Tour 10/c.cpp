#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 7;
const int64_t k = 31;
const int64_t mod = 1e9 + 7;

vector <map <int64_t, vector <int>>> posesb(maxn), posese(maxn);

int get(char c) { return c - 'a' + 1; }


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string s; cin >> s;
    int n = (int)s.size();
    for (int i = 0; i < n; i++) {
        int64_t cur = 0;
        for (int j = i; j < n; j++) {
            cur = (cur * k + get(s[j])) % mod;
            posesb[j - i + 1][cur].push_back(i);
            posese[j - i + 1][cur].push_back(j);
        }
    }
    int64_t ans = 0;
    vector <vector <int>> cnt(n, vector <int> (n));
    for (int i = 1; i < n - 1; i++) {
        int64_t able1 = 0, cnt1 = 0, curpow = 1, cur = 0;
        for (int j = i; j >= 1 && (i - j + 1) <= (i + 1) / 2; j--) {
            cur = (cur + get(s[i]) * curpow % mod) % mod;
            if (posese[i - j + 1].find(cur) != posese[i - j + 1].end()) {
                cnt1 += (lower_bound(posese[i - j + 1][cur].begin(), posese[i - j + 1][cur].end(), j) - posese[i - j + 1][cur].begin());
            }
            curpow *= k;
            if (cnt1 > 0) able1++;
        }
        int64_t able2 = 0, cnt2 = 0; cur = 0;
        for (int j = i + 1; (j - (i + 1) + 1) <= (n - i - 1) / 2; j++) {
            cur = (cur * k + get(s[j])) % mod;
            if (posesb[j - (i + 1) + 1].find(cur) != posesb[j - (i + 1) + 1].end()) {
                cnt2 += (int)posesb[j - (i + 1) + 1][cur].size() - (upper_bound(posesb[j - (i + 1) + 1][cur].begin(), posesb[j - (i + 1) + 1][cur].end(), j) - posesb[j - (i + 1) + 1][cur].begin());
            }
            if (cnt2 > 0) {
                cnt
            }
        }
    }
    cout << ans << '\n';
    return 0;
}