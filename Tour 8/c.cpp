#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 7;
const int64_t k = 31;
const int64_t mod = 1e9 + 7;

int64_t bp(int64_t n, int64_t m) {
    int64_t ans = 1;
    while (m) {
        if (m & 1) ans = ans * n % mod;
        n = n * n % mod;
        m >>= 1;
    }
    return ans;
}

int64_t add(int64_t a, int64_t b) { return (a + b) % mod; }
int64_t rem(int64_t a, int64_t b) { return (a - b + mod) % mod; }
int64_t mul(int64_t a, int64_t b) { return a * b % mod; }
int64_t del(int64_t a, int64_t b) { return mul(a, bp(b, mod - 2)); }

vector <int64_t> p(maxn), phash(maxn);

int64_t hash_substr(int l, int r) {
    return del(rem(phash[r + 1], phash[l]), p[l]);
}

vector <map <int64_t, int>> cnt(maxn);
vector <int> mx(maxn, 0);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string s; cin >> s;
    int sz = (int)s.size();
    p[0] = 1;
    for (int i = 1; i < maxn; i++) p[i] = (p[i - 1] * k) % mod;
    for (int i = 0; i < sz; i++) phash[i + 1] = (phash[i] + mul(s[i] - 'a' + 1, p[i])) % mod;
    int n, k; cin >> n >> k;
    for (int i = 0; i < n; i++) {
        string t; cin >> t;
        int cursz = (int)t.size();
        int64_t h = 0, m = 1, fhash = 0, lhash = 0;
        bool pref = true;
        for (int j = 0; j < cursz && j < sz; j++) {
            int64_t x = (int)(t[j] - 'a' + 1);
            if (pref && hash_substr(0, j) != (h + p[j] * x) % mod) {
                pref = false;
                fhash = h;
                lhash = j;  
            }
            h = (h + p[j] * x) % mod;
            if (!pref) {
                if (add(fhash, mul(p[lhash], hash_substr(sz - 1 - j + lhash, sz - 1))) == h) {
                    cnt[sz - (j + 1)][h]++;
                    mx[sz - (j + 1)] = max(cnt[sz - (j + 1)][h], mx[sz - (j + 1)]);
                }
            } else {
                cnt[sz - (j + 1)][h]++;
                mx[sz - (j + 1)] = max(cnt[sz - (j + 1)][h], mx[sz - (j + 1)]);
            }
        }
    }
    for (int i = 1; i <= k; i++) cout << mx[i] << ' ';
    return 0;
}