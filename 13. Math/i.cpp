#include <bits/stdc++.h>
using namespace std;

const int maxa = 1e7;
const int maxn = 4e5;

vector <string> primes;

void solve() {
    int n, k; cin >> n >> k;
    string s = "";
    for (int i = 0; i < n; i++) s += primes[i];
    vector <vector <int>> inds(10);
    for (int j = 0; j < (int)s.size(); j++) inds[s[j] - '0'].push_back(j);
    for (int i = 0; i < 10; i++) {
        inds[i].push_back((int)s.size());
        reverse(inds[i].begin(), inds[i].end());
    }
    int pos = 0, good = 0;
    while (pos < k + good && k + good < (int)s.size()) {
        int d = 9;
        while (inds[d].back() > k + good) d--;
        for (int i = pos; i < inds[d].back(); i++) inds[s[i] - '0'].pop_back();
        pos = inds[d].back() + 1, good++;
        inds[d].pop_back();
        cout << char('0' + d);
    }
    if (pos == k + good) {
        for (int i = pos; i < (int)s.size(); i++) cout << s[i];
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t; cin >> t;
    vector <int> p(maxa, 1);
    for (int i = 2; i < maxa && (int)primes.size() < maxn; i++) {
        if (p[i]) {
            primes.push_back(to_string(i));
            if (1LL * i * i < maxa) for (int j = i * i; j < maxa; j += i) p[j] = 0;
        }
    }
    while (t--) solve();
    return 0;
}