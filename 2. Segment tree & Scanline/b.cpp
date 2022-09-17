#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;

struct tree {
    struct node {
        int64_t seg, pref, suff, sum;
    };

    int size;
    vector <node> t;

    node combine(node a, node b) {
        return {
            max({a.seg, b.seg, a.suff + b.pref}),
            max(a.pref, a.sum + b.pref),
            max(a.suff + b.sum, b.suff),
            a.sum + b.sum
        };
    };

    tree(int n) {
        size = 1;
        while (size < n) size <<= 1;
        t.resize(2 * size - 1, {-INF, -INF, -INF, -INF});
    }

    void set(int k, int x, int id, int lb, int rb) {
        if (lb + 1 == rb) {
            if (x == 0) t[id] = {1, 1, 1, 1};
            else t[id] = {-INF, -INF, -INF, -INF};
            return;
        }
        int m = (lb + rb) / 2;
        if (k < m) set(k, x, id * 2 + 1, lb, m);
        else set(k, x, id * 2 + 2, m, rb);
        t[id] = combine(t[id * 2 + 1], t[id * 2 + 2]);
    }

    void set(int k, int x) {
        set(k, x, 0, 0, size);
    }

    node get(int l, int r, int id, int lb, int rb) {
        if (l >= rb || r <= lb) return {0, 0, 0, 0};
        if (l <= lb && rb <= r) return t[id];
        int m = (lb + rb) / 2;
        node s1 = get(l, r, id * 2 + 1, lb, m);
        node s2 = get(l, r, id * 2 + 2, m, rb);
        return combine(s1, s2);
    }

    node get(int l, int r) {
        return get(l, r, 0, 0, size);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    tree t(n);
    for (int i = 0, c; i < n; i++) {
        cin >> c;
        t.set(i, c);
    }
    int q; cin >> q;
    for (int i = 0, l, r; i < q; i++) {
        string s; cin >> s >> l >> r;
        if (s == "QUERY") {
            auto res = t.get(l - 1, r);
            cout << res.seg << '\n';
        } else {
            t.set(l - 1, r);
        }
    }
    return 0;
}