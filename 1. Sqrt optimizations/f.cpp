#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 7;

struct node {
    bool is_light = false;
    int v;
    vector <int> cnt;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m; cin >> n >> m;
    vector <node> nodes(n);
    for (int i = 0; i < n; i++) cin >> nodes[i].v;
    vector <vector <int>> g(n), heavies(n);
    int64_t cur = 0;
    for (int i = 0, v, u; i < m; i++) {
        cin >> v >> u; v--, u--;
        g[v].push_back(u);
        g[u].push_back(v);
        if (nodes[v].v != nodes[u].v) cur++;
    }
    for (int i = 0; i < n; i++) {
        int sz = (int)g[i].size();
        if (sz < 500) nodes[i].is_light = true;
        else {
            for (int u : g[i]) {
                nodes[i].cnt.resize(MAXN);
                nodes[i].cnt[nodes[u].v]++;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (!nodes[i].is_light) {
            for (int u : g[i]) {
                if (!nodes[u].is_light) heavies[i].push_back(u);
            }
        }
    }
    cin >> m;
    for (int p = 0, c, v; p < m; p++) {
        cin >> c >> v; c--;
        if (nodes[c].v == v) {
            cout << cur << '\n';
            continue;
        }
        if (nodes[c].is_light) {
            for (int u : g[c]) {
                if (!nodes[u].is_light) {
                    nodes[u].cnt[nodes[c].v]--;
                    nodes[u].cnt[v]++;
                }
                if (nodes[u].v == nodes[c].v) cur++;
                if (nodes[u].v == v) cur--;
            }
            nodes[c].v = v;
        } else {
            for (int u : heavies[c]) {
                nodes[u].cnt[nodes[c].v]--;
                nodes[u].cnt[v]++;
            }
            cur -= nodes[c].cnt[v];
            cur += nodes[c].cnt[nodes[c].v];
            nodes[c].v = v;
        }
        cout << cur << '\n';
    }
    return 0;
}