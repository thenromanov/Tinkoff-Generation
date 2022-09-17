#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 179;

int64_t ans = 0;
vector <int> p(maxn), sz(maxn), pxor(maxn);
vector <map <int, vector <int>>> xors(maxn);

void unite(int v, int u, int c) {
    if (sz[p[v]] < sz[p[u]]) swap(v, u);
    int pv = p[v], pu = p[u];
    for (auto it : xors[pu]) {
        for (int x : it.second) {
            ans += (int)xors[pv][pxor[v] ^ pxor[u] ^ c ^ pxor[x]].size();
        }
    }
    int prev = pxor[u];
    for (auto it : xors[pu]) {
        for (int x : it.second) {
            pxor[x] ^= prev ^ c ^ pxor[v];
            xors[pv][pxor[x]].push_back(x);
            p[x] = pv;
        }
    }
    sz[pv] += sz[pu];
    xors[pu].clear();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    vector <vector <int>> v(n - 1, vector <int> (3));
    for (auto& u : v) {
        cin >> u[0] >> u[1] >> u[2];
        u[0]--, u[1]--;
    }
    for (int i = 0; i < n; i++) {
        p[i] = i;
        xors[i][0].push_back(i);
        sz[i] = 1;
    }
    vector <int> order(n - 1);
    vector <int64_t> res(n);
    for (int& u : order) cin >> u, u--;
    for (int i = n - 2; i >= 0; i--) {
        unite(v[order[i]][0], v[order[i]][1], v[order[i]][2]);
        res[i] = ans;
    }
    for (auto u : res) cout << u << '\n';
    return 0;
}