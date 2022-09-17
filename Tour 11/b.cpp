#include <bits/stdc++.h>
using namespace std;

vector <vector <pair <int, int>>> g;
vector <int> used, sz;
pair <int, int> ans = {INT_MAX, INT_MAX};
int k, t;

int get_size(int v, int p = -1) {
    if (used[v]) return 0;
    sz[v] = 1;
    for (auto [u, l] : g[v]) {
        if (u != p && !used[u]) {
            get_size(u, v);
            sz[v] += sz[u];
        }
    }
    return sz[v];
}

int find_centroid(int v, int p, int n) {
    for (auto [u, l] : g[v]) {
        if (u != p && !used[u] && sz[u] > n / 2) return find_centroid(u, v, n);
    }
    return v;
}

void find_dist(int v, int p, set <pair <pair <int, int64_t>, int>>& nds, int h = 0, int64_t l = 0) {
    if (used[v]) return;
    nds.insert({{h, l}, v});
    for (auto [u, d] : g[v]) {
        if (u != p) find_dist(u, v, nds, h + 1, l + d);
    }
}

void decompose(int v) {
    get_size(v);
    int c = find_centroid(v, -1, sz[v]);
    used[c] = 1;
    set <pair <pair <int, int64_t>, int>> nds;
    find_dist(c, -1, nds);
    for (auto [u, l] : g[c]) {
        set <pair <pair <int, int64_t>, int>> cur;
        find_dist(u, c, cur, 1, l);
        for (auto [ds, e] : cur) {
            if (k - ds.first >= 0 && t - ds.second >= 0) {
                auto it = nds.lower_bound({{k - ds.first, t - ds.second}, -1});
                if (it != nds.end() && it->first.first == k - ds.first && it->first.second == t - ds.second) {
                    pair <int, int> mb = {e, it->second};
                    if (mb.first > mb.second) swap(mb.first, mb.second);
                    ans = min(ans, mb);
                }
            }
        }
        for (auto e : cur) nds.insert(e);
    }
    for (auto [u, l] : g[c]) {
        if (!used[u]) decompose(u);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n >> t >> k;
    if (k == 0) {
        if (t == 0) cout << 1 << ' ' << 1 << '\n';
        else cout << 0 << ' ' << 0 << '\n';
        return 0;
    }
    g.resize(n), used.resize(n), sz.resize(n);
    for (int i = 0, v, u, c; i < n - 1; i++) {
        cin >> v >> u >> c; v--, u--;
        g[v].push_back({u, c});
        g[u].push_back({v, c});
    }
    decompose(0);
    if (ans.first == INT_MAX) ans = {-1, -1};
    cout << ans.first + 1 << ' ' << ans.second + 1 << '\n';
    return 0;
}