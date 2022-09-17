#include <bits/stdc++.h>
using namespace std;

vector <vector <int>> g;
vector <int> comp, sz;
int cnt = 0;

void dfs(int v, int c) {
    comp[v] = c;
    sz[c]++;
    for (auto u : g[v]) {
        if (comp[u] == -1) dfs(u, c);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m; cin >> n >> m;
    g.resize(n), comp.resize(n, -1), sz.resize(n);
    for (int i = 0, v, u; i < m; i++) {
        cin >> v >> u; v--, u--;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    for (int i = 0; i < n; i++) {
        if (comp[i] == -1) {
            dfs(i, cnt++);
        }
    }
    if (cnt > 2) {
        cout << "No\n";
        return 0;
    }
    for (int i = 0; i < n; i++) {
        if (g[i].size() < sz[comp[i]] - 1) {
            cout << "No\n";
            return 0;
        }
    }
    cout << "Yes\n";
    return 0;
}