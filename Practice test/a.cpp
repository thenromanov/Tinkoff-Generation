#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 179;

bool ok = true;
vector <int> l(maxn), r(maxn);
vector <pair <int, int>> rng(maxn);

int dfs(int v) {
    if (l[v] == -1 && r[v] == -1) return 0;
    int cnt = 0;
    if (l[v] != -1) cnt += dfs(l[v]);
    if (r[v] != -1) cnt += dfs(r[v]);
    if (rng[r[v]].second <= rng[l[v]].first) cnt++, rng[v].first = rng[r[v]].first, rng[v].second = rng[l[v]].second;
    else if (rng[l[v]].second <= rng[r[v]].first) rng[v].first = rng[l[v]].first, rng[v].second = rng[r[v]].second;
    else ok = false;
    return cnt;
}

void solve() {
    int n; cin >> n; ok = true;
    for (int i = 0, ll, rr; i < n; i++) {
        cin >> ll >> rr;
        if (ll == -1) rng[i] = {rr, rr}, l[i] = -1, r[i] = -1;
        else l[i] = ll - 1, r[i] = rr - 1;
    }
    int ans = dfs(0);
    cout << (ok ? ans : -1) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}