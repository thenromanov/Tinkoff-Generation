#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 7;

struct ft {
    int n;
    vector <int64_t> t;

    ft(int n) {
        this->n = n;
        t.resize(n);
    }

    int64_t sum(int r) {
        int64_t ans = 0;
        for (; r > 0; r -= r & -r) ans += t[r];
        return ans;
    }

    void inc(int k, int64_t x) {
        for (; k <= n; k += k & -k) t[k] += x;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    ft t(MAXN);
    vector <pair <int64_t, int>> pref(n + 1);
    pref[0].second = 1;
    for (int i = 1; i <= n; i++) {
        cin >> pref[i].first;
        if (i) pref[i].first += pref[i - 1].first;
        pref[i].second = i + 1;
    }
    int64_t p; cin >> p;
    for (int i = 1; i <= n; i++) pref[i].first -= p * i;
    sort(pref.begin(), pref.end());
    int64_t ans = 0;
    for (auto u : pref) {
        ans += t.sum(u.second);
        t.inc(u.second, 1);
    }
    cout << ans;
    return 0;
}