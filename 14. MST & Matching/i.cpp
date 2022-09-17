#include <bits/stdc++.h>
using namespace std;

struct tree {
    int size;
    vector <pair <int, int>> t;

    tree(int n) {
        size = 1;
        while (size < n) size <<= 1;
        t.resize(2 * size - 1, {INT_MAX, INT_MAX});
    }

    void set(int k, int x, int id, int lb, int rb) {
        if (lb + 1 == rb) {
            t[id] = {x, k};
            return;
        }
        int m = (lb + rb) / 2;
        if (k < m) set(k, x, id * 2 + 1, lb, m);
        else set(k, x, id * 2 + 2, m, rb);
        t[id] = min(t[id * 2 + 1], t[id * 2 + 2]);
    }

    void set(int k, int x) {
        set(k, x, 0, 0, size);
    }

    pair <int, int> get(int l, int r, int id, int lb, int rb) {
        if (l >= rb || r <= lb) return {INT_MAX, INT_MAX};
        if (l <= lb && rb <= r) return t[id];
        int m = (lb + rb) / 2;
        return min(get(l, r, id * 2 + 1, lb, m), get(l, r, id * 2 + 2, m, rb));
    }

    pair <int, int> get(int l, int r) {
        return get(l, r, 0, 0, size);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    tree stree(n + 1);
    for (int i = 0; i < n; i++) stree.set(i, INT_MAX);
    stree.set(n, 0);
    vector <pair <int, int>> a = {{0, 0}};
    vector <int> b(n + 1), p(n + 1, -1), from(n + 1, -1), maxleft(n + 1);
    for (int i = 1, v; i <= n; i++) {
        cin >> v;
        a.push_back({max(i - v, 0), i});
        maxleft[i] = max(i - v, 0);
    }
    sort(a.rbegin(), a.rend());
    for (int i = 1; i <= n; i++) {
        cin >> b[i]; b[i] = min(i + b[i], n);
    }
    int pos = 0;
    for (int j = n - 1; j >= 0; j--) {
        while (pos < a.size() && a[pos].first > j) stree.set(a[pos++].second, INT_MAX);
        pair <int, int> res = stree.get(j + 1, n + 1);
        pair <int, int> cur = stree.get(b[j], b[j] + 1);
        if (res.first == INT_MAX) continue;
        if (cur.first > res.first + 1) {
            if (maxleft[b[j]] > j) continue;
            stree.set(b[j], res.first + 1);
            p[j] = res.second;
            from[b[j]] = j;
        }
    }
    from[n] = n;
    if (p[0] == -1) {
        cout << -1 << '\n';
        return 0;
    }
    vector <int> ans;
    int cur = 0;
    while (cur != n) {
        ans.push_back(cur);
        cur = from[p[cur]];
    }
    cout << ans.size() << '\n';
    reverse(ans.begin(), ans.end());
    for (auto u : ans) cout << u << ' ';
    return 0;
}
