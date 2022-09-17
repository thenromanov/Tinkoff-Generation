#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2,sse3,sse3,sse4,popcnt,abm,mmx,avx,avx2")

#include <bits/stdc++.h>
using namespace std;

const pair <int, int> inf = {INT_MAX, INT_MAX};

vector <int> p, sz, c;

set <pair <int, int>> st;

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m; cin >> n >> m;
    int comps = n;
    p.resize(n), sz.resize(n, 1), c.resize(n);
    iota(p.begin(), p.end(), 0);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        st.insert({c[i], i});
    }
    int64_t res = 0;
    while (comps > 1) {
        vector <vector <int>> nodes(n);
        for (int i = 0; i < n; i++) nodes[find(i)].push_back(i);
        for (auto nd : nodes) {
            for (auto i : nd) st.erase({c[i], i});
            pair <int, int> ans = inf;
            for (auto i : nd) {
                auto f = st.begin();
                auto s = st.lower_bound({m - c[i], -1});
                pair <int, int> ans1 = inf, ans2 = inf;
                if (f != st.end() && f->first + c[i] < m) ans1 = *f, ans1.first += c[i];
                if (s != st.end()) ans2 = *s, ans2.first += c[i] - m;
                ans = min({ans, ans1, ans2});
            }
            if (ans.first != INT_MAX && nd.size() && find(ans.second) != find(nd.back())) {
                res += ans.first;
                unite(ans.second, nd.back());
                comps--;
            }
            for (auto i : nd) st.insert({c[i], i});
        }
    }
    cout << res << '\n';
    return 0;
}