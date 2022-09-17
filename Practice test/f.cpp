#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e5 + 179;

struct ft {
    int n;
    vector <int> t;

    ft(int n) {
        this->n = n;
        t.resize(n + 1);
    }

    void inc(int k, int x) {
        for (; k <= n; k += k & -k) t[k] += x;
    }

    int sum(int r) {
        int ans = 0;
        for (; r > 0; r -= r & -r) ans += t[r];
        return ans;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void fill_null() {
        t.assign(n + 1, 0);
    }
};

struct query {
    int x, y1, y2, id, is_open;

    bool operator< (const query& o) const {
        return x < o.x;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int a, b; cin >> a >> b;
    int n, q; cin >> n >> q;
    vector <pair <int, int>> nodes, edges;
    vector <query> qs;
    for (int i = 0, x, y; i < n - 1; i++) {
        char c; cin >> c >> x >> y;
        if (c == 'v') nodes.push_back({2 * x, 2 * y}), nodes.push_back({2 * x, 2 * y + 2}), edges.push_back({2 * x, 2 * y + 1});
        else nodes.push_back({2 * x, 2 * y}), nodes.push_back({2 * x + 2, 2 * y}), edges.push_back({2 * x + 1, 2 * y});
    }
    sort(nodes.begin(), nodes.end());
    nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
    sort(edges.begin(), edges.end());
    edges.erase(unique(edges.begin(), edges.end()), edges.end());
    for (int i = 0, x1, y1, x2, y2; i < q; i++) {
        cin >> x1 >> y1 >> x2 >> y2;
        qs.push_back({2 * x1, 2 * y1, 2 * y2, i, 1});
        qs.push_back({2 * x2, 2 * y1, 2 * y2, i, 0});
    }
    sort(qs.begin(), qs.end());
    vector <int> ansnodes(q), ansedges(q);
    int pos = 0;
    ft tree(maxn);
    for (auto q : qs) {
        if (q.is_open) continue;
        while (pos < (int)nodes.size() && nodes[pos].first <= q.x) tree.inc(nodes[pos++].second, 1);
        ansnodes[q.id] += tree.sum(q.y1, q.y2);
    }
    tree.fill_null(), pos = 0;
    for (auto q : qs) {
        if (!q.is_open) continue;
        while (pos < (int)nodes.size() && nodes[pos].first < q.x) tree.inc(nodes[pos++].second, 1);
        ansnodes[q.id] -= tree.sum(q.y1, q.y2);
    }
    tree.fill_null(), pos = 0;
    for (auto q : qs) {
        if (q.is_open) continue;
        while (pos < (int)edges.size() && edges[pos].first <= q.x) tree.inc(edges[pos++].second, 1);
        ansedges[q.id] += tree.sum(q.y1, q.y2);
    }
    tree.fill_null(), pos = 0;
    for (auto q : qs) {
        if (!q.is_open) continue;
        while (pos < (int)edges.size() && edges[pos].first < q.x) tree.inc(edges[pos++].second, 1);
        ansedges[q.id] -= tree.sum(q.y1, q.y2);
    }
    for (int i = 0; i < q; i++) cout << ansnodes[i] - ansedges[i] << '\n';
    return 0;
}