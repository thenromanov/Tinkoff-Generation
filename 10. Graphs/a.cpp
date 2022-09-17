#include <bits/stdc++.h>
using namespace std;
 
vector <vector <int>> g, t;
vector <int> used, comp, order;
 
void dfs(int v) {
    used[v] = 1;
    for (int u : g[v]) {
        if (!used[u]) dfs(u);
    }
    order.push_back(v);
}
 
void color(int v, int c) {
    comp[v] = c;
    for (int u : t[v]) {
        if (comp[u] == 0) color(u, c);
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m; 
    while (cin >> n >> m) {
        g.clear(), t.clear(), used.clear(), comp.clear();
        g.resize(2 * n), t.resize(2 * n), used.resize(2 * n), comp.resize(2 * n);
        for (int i = 0; i < m; i++) {
            int c1, c2, a, b;
            cin >> a >> c1 >> b >> c2; a = a * 2, b = b * 2;
            if (c1 == 0) a ^= 1;
            if (c2 == 0) b ^= 1;
            g[a ^ 1].push_back(b);
            g[b ^ 1].push_back(a);
            t[b].push_back(a ^ 1);
            t[a].push_back(b ^ 1);
        }
        for (int i = 0; i < 2 * n; i++) {
            if (!used[i]) dfs(i);
        }
        reverse(order.begin(), order.end());
        int cnt = 0;
        for (int v : order) {
            if (comp[v] == 0) color(v, ++cnt);
        }
        for (int i = 0; i < 2 * n; i += 2) {
            cout << (comp[i] > comp[i ^ 1]);
        }
        cout << '\n';
    }
    return 0;
}