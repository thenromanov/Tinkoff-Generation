#include <bits/stdc++.h>
using namespace std;

struct circle {
    double x, y, r;
};

struct dsu {
    vector <int> p, sz;

    dsu(int n) {
        p.resize(n), sz.resize(n, 1);
        iota(p.begin(), p.end(), 0);
    }

    int find(int v) {
        if (p[v] == v) return v;
        return p[v] = find(p[v]);
    }

    void unite(int v, int u) {
        v = find(v), u = find(u);
        if (v == u) return;
        if (sz[v] > sz[u]) swap(v, u);
        sz[u] += sz[v];
        p[v] = u;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    vector <circle> c(n);
    dsu cnm(n);
    for (int i = 0; i < n; i++) cin >> c[i].x >> c[i].y >> c[i].r;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((c[i].x - c[j].x) * (c[i].x - c[j].x) + (c[i].y - c[j].y) * (c[i].y - c[j].y) < (c[i].r + c[j].r) * (c[i].r + c[j].r)) cnm.unite(i, j);
        }
    }
    map <int, vector <circle>> mp;
    for (int i = 0; i < n; i++) {
        mp[cnm.find(i)].push_back(c[i]);
    }
    double ans = 0;
    for (auto [u, cs] : mp) {
        double maxr = 0;
        for (auto c : cs) maxr = max(maxr, c.r);
        ans += maxr * maxr;
    }
    cout << fixed << setprecision(10) << acos(-1) * ans << '\n';
    return 0;
}