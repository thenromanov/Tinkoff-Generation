#include <bits/stdc++.h>
using namespace std;

int cnt = 0;
vector <int> ans, req, p, sz;
vector <pair <int, int>> rollback;

struct query {
    int l, r, v, u;
};

int find(int v) {
    if (p[v] == v) return v;
    return find(p[v]);
}

int unite(int v, int u) {
    v = find(v), u = find(u);
    if (v == u) return 0;
    if (sz[v] > sz[u]) swap(v, u);
    rollback.push_back({u, v});
    p[v] = u;
    sz[u] += sz[v];
    cnt--;
    return 1;
}

void backup(int k) {
    while (k--) {
        sz[rollback.back().first] -= sz[rollback.back().second];
        p[rollback.back().second] = rollback.back().second;
        cnt++;
        rollback.pop_back();
    }
}

void solve(vector <query>& q, int l, int r) {
    if (req[l] == req[r]) return;
    if (q.empty()) {
        for (int i = l; i < r; i++) ans[i] = cnt;
        return;
    }
    vector <query> q1;
    int k = 0;
    for (auto u : q) {
        if (u.l <= l && r <= u.r) k += unite(u.v, u.u);
        else if (l < u.r && u.l < r) q1.push_back(u);
    }
    int m = (l + r) / 2;
    solve(q1, l, m);
    solve(q1, m, r);
    backup(k);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, k; cin >> n >> k;
    cnt = n;
    req.resize(k + 1), ans.resize(k + 1), p.resize(n), sz.resize(n, 1);
    iota(p.begin(), p.end(), 0);
    vector <query> q;
    unordered_map <int64_t, int> mp;
    for (int i = 0; i < k; i++) {
        char c; cin >> c;
        if (c != '?') {
            int v, u; cin >> v >> u; v--, u--;
            if (v == u) {
                k--, i--;
                continue;
            }
            if (v > u) swap(v, u);
            if (c == '+') mp[1LL * n * v + u] = i;
            else {
                q.push_back({mp[1LL * n * v + u], i, v, u});
                mp[1LL * n * v + u] = -1;
            }
        } else {
            req[i + 1]++;
        }
        req[i + 1] += req[i];
    }
    for (auto u : mp) {
        if (u.second != -1) q.push_back({u.second, k, int(u.first / n), int(u.first % n)});
    }
    solve(q, 0, k);
    for (int i = 0; i < k; i++) {
        if (req[i + 1] - req[i]) cout << ans[i] << '\n';
    }
    return 0;
}