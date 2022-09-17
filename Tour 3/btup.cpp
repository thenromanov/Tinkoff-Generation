#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 7;
const int64_t inf = 1e18 + 179;

vector <int> ans(maxn);
vector <vector <int>> g(maxn);
vector <pair <int64_t, int64_t>> lr(maxn), d(maxn);

pair <int64_t, int64_t> intersect(pair <int64_t, int64_t> a, pair <int64_t, int64_t> b) {
    return {max(a.first, b.first), min(a.second, b.second)};
}

void dfs(int v, int p) {
    int flag = 0;
    for (int u : g[v]) {
        if (u != p) {
            dfs(u, v);
            if (flag) d[v] = intersect(d[v], {d[u].first + lr[u].first, d[u].second + lr[u].second});
            else d[v] = {d[u].first + lr[u].first, d[u].second + lr[u].second}, flag = 1;
        }
    }
    if (d[v].first > d[v].second) d[v].second = -inf;
}

void get_ans(int v, int p, int64_t l, int64_t r) {
    if (p == -1) {
        if (d[v].first <= d[v].second) ans[v] = 1;
        if (g[v].size() != 1) l = 0, r = inf;
    } else {
        if (g[v].size() == 1) {
            if (l <= r) ans[v] = 1;
        } else {
            if (max(l, d[v].first) <= min(r, d[v].second)) ans[v] = 1;
        }
    }
    vector <pair <int64_t, int64_t>> suff;
    for (int u : g[v]) {
        if (u != p) suff.push_back({d[u].first + lr[u].first, d[u].second + lr[u].second});
    }
    suff.push_back({0, inf});
    for (int i = suff.size() - 2; i >= 0; i--) suff[i] = intersect(suff[i], suff[i + 1]);
    int pos = 0;
    for (int u : g[v]) {
        if (u != p) {
            pair <int64_t, int64_t> cur = {max(l, suff[pos + 1].first), min(r, suff[pos + 1].second)};
            if (cur.first > cur.second) cur.second = -inf;
            get_ans(u, v, cur.first + lr[v].first, cur.second + lr[v].second);
            pos++;
            l = max(l, d[u].first + lr[u].first), r = min(r, d[u].second + lr[u].second);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    for (int i = 0, v, u; i < n - 1; i++) {
        cin >> v >> u; v--, u--;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    for (int i = 0; i < n; i++) cin >> lr[i].first >> lr[i].second;
    dfs(0, -1);
    get_ans(0, -1, 0, 0);
    for (int i = 0; i < n; i++) cout << ans[i] << ' ';
    return 0;
}