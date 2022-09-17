#include <bits/stdc++.h>
using namespace std;

struct tree {
    struct node {
        int sum, promise;
    };

    int size;
    vector <node> t;

    tree(int n) {
        size = 1;
        while (size < n) size <<= 1;
        t.resize(2 * size - 1, {0, INT_MIN});
    }

    void push(int id, int lb, int rb) {
        if (t[id].promise != INT_MIN) {
            t[id].sum = (rb - lb) * t[id].promise;
            if (lb + 1 < rb) {
                t[id * 2 + 1].promise = t[id].promise;
                t[id * 2 + 2].promise = t[id].promise;
            }
            t[id].promise = INT_MIN;
        }
    }

    void upd(int l, int r, int x, int id, int lb, int rb) {
        push(id, lb, rb);
        if (l >= rb || r <= lb) return;
        if (l <= lb && rb <= r) {
            t[id].promise = x;
            push(id, lb, rb);
            return;
        }
        int m = (lb + rb) / 2;
        upd(l, r, x, id * 2 + 1, lb, m);
        upd(l, r, x, id * 2 + 2, m, rb);
        t[id].sum = t[id * 2 + 1].sum + t[id * 2 + 2].sum;
    }

    void upd(int l, int r, int x) {
        upd(l, r, x, 0, 0, size);
    }

    int get(int l, int r, int id, int lb, int rb) {
        push(id, lb, rb);
        if (l >= rb || r <= lb) return 0;
        if (l <= lb && rb <= r) return t[id].sum;
        int m = (lb + rb) / 2;
        return get(l, r, id * 2 + 1, lb, m) + get(l, r, id * 2 + 2, m, rb);
    }

    int get(int l, int r) {
        return get(l, r, 0, 0, size);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, q; cin >> n >> q;
    vector <tree> let(26, tree(n));
    string s; cin >> s;
    for (int i = 0; i < n; i++) let[s[i] - 'a'].upd(i, i + 1, 1);
    for (int i = 0, l, r, k; i < q; i++) {
        cin >> l >> r >> k;
        int count = 0;
        if (k == 0) {
            for (int p = 25; p >= 0; p--) {
                int cnt = let[p].get(l - 1, r);
                let[p].upd(l - 1, r, 0);
                let[p].upd(l - 1 + count, l - 1 + count + cnt, 1);
                count += cnt;
            }
        } else {
            for (int p = 0; p < 26; p++) {
                int cnt = let[p].get(l - 1, r);
                let[p].upd(l - 1, r, 0);
                let[p].upd(l - 1 + count, l - 1 + count + cnt, 1);
                count += cnt;
            }
        }
    }
    vector <char> ans(n);
    for (int i = 0; i < 26; i++) {
        for (int p = 0; p < n; p++) {
            if (let[i].get(p, p + 1)) ans[p] = char('a' + i);
        }
    }
    for (auto u : ans) cout << u;
    return 0;
}