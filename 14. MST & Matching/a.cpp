#include <bits/stdc++.h>
using namespace std;

bool dfs(int v, vector <vector <int>>& l, vector <int>& r, vector <int>& used) {
    if (used[v]) return false;
    used[v] = true;
    for (int u : l[v]) {
        if (r[u] == -1 || dfs(r[u], l, r, used)) {
            r[u] = v;
            return true;
        }
    }
    return false;
}

void get(int v, vector <vector <int>>& l, vector <int>& r, vector <int>& ml, vector <int>& mr) {
    if (ml[v]) return;
    ml[v] = true;
    for (int u : l[v]) {
        if (r[u] != -1) {
            mr[u] = true;
            get(r[u], l, r, ml, mr);
        }
    }
}

vector <int> matching(int n, int m, vector <vector <int>>& g) {
    vector <int> r(m, -1), used(n);
    for (int i = 0; i < n; i++) {
        if (dfs(i, g, r, used)) used.assign(n, 0);
    }
    return r;
}

void solve() {
    int n, m; cin >> n >> m;
    vector <vector <int>> g(n);
    vector <int> nd(m, 1);
    for (int i = 0; i < n; i++) {
        nd.assign(m, 1);
        int v;
        while (cin >> v && v) nd[v - 1] = 0;
        for (int j = 0; j < m; j++) {
            if (nd[j]) g[i].push_back(j);
        }
    }
    vector <int> mt = matching(n, m, g);
    vector <int> used(n, 1);
    for (int l : mt) {
        if (l != -1) used[l] = 0;
    }
    vector <int> ml(n), mr(m);
    for (int i = 0; i < n; i++) {
        if (used[i]) get(i, g, mt, ml, mr);
    }
    vector <int> la, ra;
    for (int i = 0; i < n; i++) {
        if (ml[i]) la.push_back(i + 1);
    }
    for (int i = 0; i < m; i++) {
        if (!mr[i]) ra.push_back(i + 1);
    }
    cout << la.size() + ra.size() << '\n';
    cout << la.size() << ' ' << ra.size() << '\n';
    for (int u : la) cout << u << ' ';
    cout << '\n';
    for (int u : ra) cout << u << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}