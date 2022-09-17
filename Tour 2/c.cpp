#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 7;

struct dsu {
    vector <int> p, s;

    dsu(int size) {
        p.resize(size);
        for (int i = 0; i < size; i++) p[i] = i;
        s.resize(size, 1);
    }

    int find(int v) {
        if (p[v] == v) return v;
        return p[v] = find(p[v]);
    }

    int unite(int v, int u) {
        v = find(v), u = find(u);
        if (s[v] > s[u]) swap(v, u);
        s[u] += s[v];
        p[v] = u;
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m; cin >> n >> m;
    dsu able(n);
    vector <int> v(n);
    for (int& u : v) cin >> u;
    for (int i = 0, c; i < m; i++) {
        cin >> c;
        if (c == 1) {
            int a, b; cin >> a >> b;
            able.unite(a - 1, b - 1);
        } else if (c == 2) {
            int a, b; cin >> a >> b;
            swap(v[a - 1], v[b - 1]);
        } else if (c == 3) {
            
        }
    }
    return 0;
}