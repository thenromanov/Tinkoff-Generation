#include <bits/stdc++.h>
using namespace std;

struct tree {
    int n;
    vector <int> t;

    tree() {}

    tree(int n) {
        this->n = n;
        t.resize(2 * n + 1);
    }

    void modify(int p, int x) {
        for (t[p += n] = x; p > 1; p >>= 1) t[p >> 1] = max(t[p], t[p ^ 1]);
    }

    int query(int l, int r) {
        int res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = max(res, t[l++]);
            if (r & 1) res = max(res, t[--r]);
        }
        return res;
    }
};

struct centroid {
    int v, sub, l;
};

vector <vector <int>> g;
vector <vector <centroid>> dist;
vector <int> used, sz;
vector <tree> dp;

int get_size(int v, int p = -1) {
    if (used[v]) return 0;
    sz[v] = 1;
    for (int u : g[v]) {
        if (u != p) sz[v] += get_size(u, v);
    }
    return sz[v];
}

int get_centroid(int v, int p, int n) {
    for (int u : g[v]) {
        if (u != p && !used[u] && sz[u] > n / 2) return get_centroid(u, v, n);
    }
    return v;
}

void get_dist(int v, int p, int c, int h = 0, int sub = 0) {
    dist[v].push_back({c, sub, h});
    for (int u : g[v]) {
        if (u != p && !used[u]) {
            if (c == v) sub++;
            get_dist(u, v, c, h + 1, sub);
        }
    }
    if (c == v) dp[v] = tree(sub + 1);
}

void decompose(int v) {
    get_size(v);
    int c = get_centroid(v, -1, sz[v]);
    get_dist(c, -1, c);
    used[c] = 1;
    for (int u : g[c]) {
        if (!used[u]) decompose(u);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    g.resize(n), dist.resize(n), used.resize(n), sz.resize(n), dp.resize(n);
    vector <pair <int, int>> s(n);
    for (int i = 0; i < n; i++) cin >> s[i].first, s[i].second = i;
    for (int i = 0, v, u; i < n - 1; i++) {
        cin >> v >> u; v--, u--;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    decompose(0);
    sort(s.rbegin(), s.rend());
    int64_t ans = 0;
    for (auto [x, v] : s) {
        int mx = 0;
        for (auto [u, sub, l] : dist[v]) {
            int prev = dp[u].query(sub, sub + 1);
            dp[u].modify(sub, 0);
            mx = max(mx, dp[u].query(0, dp[u].n) + l);
            dp[u].modify(sub, max(prev, l));
        }
        ans = max(ans, (int64_t)mx * x);
    }
    cout << ans << '\n';
    return 0;
}