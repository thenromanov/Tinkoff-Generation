#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e3 + 7;

bool found = false;
vector <vector <int>> g(maxn);
vector <int> used(maxn);

void dfs(int v) {
    used[v] = 1;
    for (int u : g[v]) {
        if (used[u] == 1) found = 1;
        else if (used[u] == 0) dfs(u);
    }
    used[v] = 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= n - i; j++) {
            char c; cin >> c;
            if (c == 'R') g[i].push_back(i + j);
            else g[i + j].push_back(i);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (used[i] == 0) dfs(i);
    }
    cout << (found ? "YES\n" : "NO\n");
    return 0;
}