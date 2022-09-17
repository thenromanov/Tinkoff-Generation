#include <bits/stdc++.h>
using namespace std;

struct query {
    int t, d, c;

    bool operator< (const query& q) const {
        if (d == q.d) return t > q.t;
        return d < q.d;
    }
};

vector <vector <pair <int, int>>> g, dist;
vector <int> used, sz;
vector <vector <query>> cur;

int find_size(int v, int p = -1) {
    if (used[v]) return 0;
    sz[v] = 1;
    for (auto [u, l] : g[v]) {
        if (u != p) sz[v] += find_size(u, v);
    }
    return sz[v];
}

int find_centroid(int v, int p, int n) {
    for (auto [u, l] : g[v]) {
        if (u != p && !used[u] && sz[u] > n / 2) return find_centroid(u, v, n);
    }
    return v;
}

void find_dist(int v, int p, int c, int h = 0) {
    if (used[v]) return;
    dist[v].push_back({c, h});
    for (auto [u, l] : g[v]) {
        if (u != p) find_dist(u, v, c, h + l);
    }
}

void decompose(int v, int p = -1) {
    find_size(v);
    int c = find_centroid(v, -1, sz[v]);
    find_dist(c, -1, c);
    used[c] = 1;
    for (auto [u, l] : g[c]) {
        if (!used[u]) decompose(u, c);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    g.resize(n), dist.resize(n), used.resize(n), sz.resize(n), cur.resize(n);
    for (int i = 0; i < n; i++) cur[i].push_back({-1, 0, 0});
    for (int i = 0, v, u, w; i < n - 1; i++) {
        cin >> v >> u >> w; v--, u--;
        g[v].push_back({u, w});
        g[u].push_back({v, w});
    }
    decompose(0);
    int q, tmr = 0; cin >> q;
    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int v, d, c; cin >> v >> d >> c; v--;
            for (auto [u, l] : dist[v]) {
                while (cur[u].size() > 0 && cur[u].back().d <= d - l) cur[u].pop_back();
                cur[u].push_back({tmr, d - l, c});
            }
        } else {
            int v; cin >> v; v--;
            int mxt = INT_MIN, curc = -1;
            for (auto [u, l] : dist[v]) {
                int ll = 0, rr = (int)cur[u].size();
                while (ll + 1 < rr) {
                    int m = (ll + rr) / 2;
                    if (cur[u][m].d < l) rr = m;
                    else ll = m; 
                }
                if (ll >= 0 && ll < (int)cur[u].size() && cur[u][ll].d >= l && cur[u][ll].t > mxt) {
                    mxt = cur[u][ll].t;
                    curc = cur[u][ll].c;
                }
            }
            cout << curc << '\n';
        }
        tmr++;
    }
    return 0;
}