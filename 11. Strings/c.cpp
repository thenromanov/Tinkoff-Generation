#include <bits/stdc++.h>
using namespace std;

const int64_t x = 17957239;
const int64_t mod1 = 1e9 + 9;
const int64_t mod2 = 1e9 + 7;

mt19937 gena;

vector <vector <int>> g;
vector <int64_t> c, h1, h2;

map <pair <int64_t, int64_t>, int64_t> cnt;
map <int64_t, int> rnd;

void dfs(int v, int p = -1) {
    if (rnd.find(c[v]) == rnd.end()) rnd[c[v]] = gena();
    h1[v] = rnd[c[v]], h2[v] = rnd[c[v]];
    for (int u : g[v]) {
        if (u != p) {
            dfs(u, v);
            h1[v] = (h1[v] * (h1[u] ^ x) % mod1) % mod1;
            h2[v] = (h2[v] * (h2[u] ^ x) % mod2) % mod2;
        }
    }
    cnt[{h1[v], h2[v]}]++;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    g.resize(n), c.resize(n), h1.resize(n), h2.resize(n);
    for (int i = 0, v, u; i < n - 1; i++) {
        cin >> v >> u; v--, u--;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    for (int i = 0; i < n; i++) cin >> c[i];
    dfs(0);
    int64_t ans = 0;
    for (auto u : cnt) {
        ans += (u.second - 1) * (u.second) / 2;
    }
    cout << ans << '\n';
    return 0;
}