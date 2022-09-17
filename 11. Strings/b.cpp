#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 7;
const int64_t k = 107;
const int64_t mod = 1e9 + 9;

vector <int64_t> pwr(maxn);
vector <int64_t> phash(maxn);

int get(char c) {
    return int(c) - 31;
}

int64_t get_hash(int l, int r) {
    return (phash[r + 1] - phash[l] * pwr[r - l + 1] % mod + mod) % mod;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    pwr[0] = 1; for (int i = 1; i < maxn; i++) pwr[i] = (pwr[i - 1] * k) % mod;
    string s; cin >> s;
    int n = (int)s.size();
    for (int i = 0; i < (int)s.size(); i++) {
        phash[i + 1] = (phash[i] * k + get(s[i])) % mod;
    }
    set <int> used;
    vector <int> ind;
    for (int i = 0; i < n; i++) {
        int64_t cur = (get_hash(i + 1, n - 1) * pwr[i + 1] % mod + get_hash(0, i)) % mod;
        if (used.find(cur) == used.end()) {
            ind.push_back(i);
            used.insert(cur);
        }
    }
    int k; cin >> k; k--;
    if ((int)ind.size() <= k) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    sort(ind.begin(), ind.end(), [&](const int& a, const int& b) {
        int l = 0, r = n;
        while (l + 1 < r) {
            int m = (l + r) / 2;
            int64_t fhash = get_hash(a + 1, min(a + m, n - 1)), shash = get_hash(b + 1, min(b + m, n - 1));
            if (a + m - 1 > n - 1) fhash = (fhash * pwr[a + m - n] % mod + get_hash(0, a + m - n)) % mod;
            if (b + m - 1 > n - 1) shash = (shash * pwr[b + m - n] % mod + get_hash(0, b + m - n)) % mod;
            if (fhash == shash) l = m;
            else r = m;
        }
        return s[(a + r) % n] <= s[(b + r) % n];
    });
    for (int i = ind[k] + 1; i < n; i++) cout << s[i];
    for (int i = 0; i <= ind[k]; i++) cout << s[i];
    return 0;
}