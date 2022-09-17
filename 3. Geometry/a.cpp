#include <bits/stdc++.h>
using namespace std;

struct dsu {
    vector <int> p, s;

    dsu(int n) {
        p.resize(n);
        for (int i = 0; i < n; i++) p[i] = i;
        s.resize(n, 1);
    }

    int find(int v) {
        if (p[v] == v) return v;
        return p[v] = find(p[v]);
    }

    void unite(int v, int u) {
        v = find(v), u = find(u);
        if (v == u) return;
        if (s[v] > s[u]) swap(v, u);
        s[u] += s[v];
        p[v] = u;
    }
};

struct circle {
    double x, y, r;
};

double dist(circle a, circle b) {
    return hypot(a.x - b.x, a.y - b.y) - a.r - b.r;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, w, h; cin >> n >> m >> w >> h;
    vector <circle> v(n);
    for (auto& u : v) cin >> u.x >> u.y >> u.r;
    vector <pair <double, pair <int, int>>> intersect;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            intersect.push_back({dist(v[i], v[j]) / 2, {i, j}});
        }
    }
    sort(intersect.begin(), intersect.end());
    const int lb = n, ub = n + 1, rb = n + 2, db = n + 3;
    dsu cnm(n + 4);
    vector <vector <int>> q(m, vector <int> (3));
    for (int i = 0; i < m; i++) {
        cin >> q[i][0] >> q[i][1];
        q[i][1]--; 
        q[i][2] = i;
    }
    sort(q.begin(), q.end());
    vector <string> ans(m);
    int pos = 0;
    for (int i = 0; i < m; i++) {
        while (pos < (int)intersect.size() && intersect[pos].first < q[i][0]) cnm.unite(intersect[pos++].second.first, intersect[pos].second.second);
        for (int j = 0; j < n; j++) {
            if (v[j].x - v[j].r - 2 * q[i][0] < 0) cnm.unite(j, lb);
            if (v[j].x + v[j].r + 2 * q[i][0] > w) cnm.unite(j, rb);
            if (v[j].y - v[j].r - 2 * q[i][0] < 0) cnm.unite(j, db);
            if (v[j].y + v[j].r + 2 * q[i][0] > h) cnm.unite(j, ub);
        }
        vector <int> able(4, 1);
        if (q[i][1] == 0 && cnm.find(lb) == cnm.find(db)) able = {0, 0, 0, 0};
        if (q[i][1] == 1 && cnm.find(db) == cnm.find(rb)) able = {0, 0, 0, 0};
        if (q[i][1] == 2 && cnm.find(rb) == cnm.find(ub)) able = {0, 0, 0, 0};
        if (q[i][1] == 3 && cnm.find(ub) == cnm.find(lb)) able = {0, 0, 0, 0};
        if (cnm.find(lb) == cnm.find(db)) able[0] = 0;
        if (cnm.find(db) == cnm.find(rb)) able[1] = 0;
        if (cnm.find(rb) == cnm.find(ub)) able[2] = 0;
        if (cnm.find(ub) == cnm.find(lb)) able[3] = 0;
        if (q[i][1] == 0) {
            if (cnm.find(lb) == cnm.find(rb)) able[2] = able[3] = 0;
            if (cnm.find(ub) == cnm.find(db)) able[1] = able[2] = 0;
        }
        if (q[i][1] == 1) {
            if (cnm.find(lb) == cnm.find(rb)) able[2] = able[3] = 0;
            if (cnm.find(ub) == cnm.find(db)) able[0] = able[3] = 0;
        }
        if (q[i][1] == 2) {
            if (cnm.find(lb) == cnm.find(rb)) able[0] = able[1] = 0;
            if (cnm.find(ub) == cnm.find(db)) able[0] = able[3] = 0;
        }
        if (q[i][1] == 3) {
            if (cnm.find(lb) == cnm.find(rb)) able[0] = able[1] = 0;
            if (cnm.find(ub) == cnm.find(db)) able[1] = able[2] = 0;
        }
        able[q[i][1]] = 1;
        for (int j = 0; j < 4; j++) {
            if (able[j]) ans[q[i][2]] += to_string(j + 1);
        }
    }
    for (auto u : ans) cout << u << '\n';
    return 0;
}