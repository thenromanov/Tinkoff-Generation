#include <bits/stdc++.h>
using namespace std;

struct d {
    int h, m, x, y;

    d() {};
    d(int h, int m, int x, int y) : h(h), m(m), x(x), y(y) {};

    bool operator< (const d& o) const {
        if (h != o.h) return h < o.h;
        if (m != o.m) return m < o.m;
        if (x != o.x) return x < o.x;
        return y < o.y;
    }

    bool operator== (const d& o) const {
        return (h == o.h) && (m == o.m) && (x == o.x) && (y == o.y);
    }
};

vector <vector <int>> g;
vector <int> used, mt;

bool dfs(int v) {
    if (used[v]) return false;
    used[v] = true;
    for (int u : g[v]) {
        if (mt[u] == -1 || dfs(mt[u])) {
            mt[u] = v;
            return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, s; cin >> n >> s;
    vector <d> v(n);
    for (int i = 0; i < n; i++) {
        string t; cin >> t >> v[i].x >> v[i].y;
        v[i].h = stoi(t.substr(0, 2)), v[i].m = stoi(t.substr(3, 2));
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    g.resize(n), mt.resize(n, -1), used.resize(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int dx = v[i].x - v[j].x, dy = v[i].y - v[j].y;
            int ti = v[i].h * 60 + v[i].m, tj = v[j].h * 60 + v[j].m;
            if (3600LL * (dx * dx + dy * dy) <= 1LL * (tj - ti) * (tj - ti) * s * s) g[i].push_back(j);
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (dfs(i)) ans++, used.assign(n, 0);
    }
    cout << n - ans << '\n';
    return 0;
}