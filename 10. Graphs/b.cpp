#include <bits/stdc++.h>
using namespace std;

const int maxm = 6e5 + 179;

int d = 0;
vector <int> used(maxm), order(maxm, -1);

void dfs(vector <vector <int>>& g, vector <int>& ans, int v, int m) {
    if ((int)ans.size() > 0) return;
    used[v] = 1;
    order[d++] = v;
    for (int u : g[v]) {
        if ((int)ans.size() > 0) return;
        if (used[u] == 1) {
            int pos = d;
            while (pos >= 0 && order[pos] != u) {
                if (order[pos] > 0 && order[pos] < m) ans.push_back(order[pos]);
                pos--;
            }
            if (u < m) ans.push_back(u);
            return;
        } else if (used[u] == 0) {
            dfs(g, ans, u, m);
            if ((int)ans.size() > 0) return;
        }
    }
    used[v] = 2;
    order[d--] = -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        order.assign(6 * m + 7, -1);
        used.assign(6 * m + 7, 0);
        d = 0;
        vector <vector <pair <int, pair <int, int>>>> tmp(n);
        for (int i = 0, v, u, c; i < m; i++) {
            cin >> v >> u >> c;
            v--, u--;
            tmp[v].push_back({c, {i, u}});
        }
        int size = m;
        vector <int> prange(n), srange(n); // [l, r)
        for (int i = 0; i < n; i++) {
            prange[i] = size;
            srange[i] = size + (int)tmp[i].size();
            size += 2 * (int)tmp[i].size();
            sort(tmp[i].begin(), tmp[i].end());
        }
        vector <vector <int>> g(size);
        vector <unordered_map <int, pair <int, int>>> mp(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < (int)tmp[i].size(); j++) {
                if (j) g[prange[i] + j].push_back(prange[i] + j - 1);
                if (j < (int)tmp[i].size() - 1) g[srange[i] + j].push_back(srange[i] + j + 1);
                g[prange[i] + j].push_back(tmp[i][j].second.first);
                g[srange[i] + j].push_back(tmp[i][j].second.first);
                if (mp[i].find(tmp[i][j].first) == mp[i].end()) mp[i][tmp[i][j].first] = {j, j};
                else mp[i][tmp[i][j].first].second++;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < (int)tmp[i].size(); j++) {
                if (mp[tmp[i][j].second.second].find(tmp[i][j].first) == mp[tmp[i][j].second.second].end()) {
                    if ((int)tmp[tmp[i][j].second.second].size() > 0) g[tmp[i][j].second.first].push_back(srange[tmp[i][j].second.second]);
                } else {
                    int pos = mp[tmp[i][j].second.second][tmp[i][j].first].first;
                    if (pos > 0) g[tmp[i][j].second.first].push_back(prange[tmp[i][j].second.second] + pos - 1);
                    pos = mp[tmp[i][j].second.second][tmp[i][j].first].second;
                    if (pos < (int)tmp[tmp[i][j].second.second].size() - 1) g[tmp[i][j].second.first].push_back(srange[tmp[i][j].second.second] + pos + 1);
                }
            }
        }
        vector <int> ans;
        for (int i = 0; i < m; i++) {
            if (!used[i]) {
                dfs(g, ans, i, m);
                if ((int)ans.size() > 0) break;
            }
        }
        if ((int)ans.size() > 0) {
            cout << (int)ans.size() << '\n';
            for (int i = (int)ans.size() - 1; i >= 0; i--) cout << ans[i] + 1 << ' ';
            cout << '\n';
        } else {
            cout << -1 << '\n';
        }
    }
    return 0;
}