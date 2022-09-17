#include <bits/stdc++.h>
using namespace std;

const int64_t fact = 100297, mod = 1e9 + 19, maxn = 1e5 + 7;

vector <int64_t> p(maxn, 1), pref(maxn, 0);

struct tree {
    struct node {
        int64_t val, promise;
    };

    int size;
    vector <node> t;

    tree(int n) {
        size = 1;
        while (size < n) size <<= 1;
        t.resize(2 * size - 1, {0LL, 0LL});
    }

    void push(int id, int lb, int rb) {
        if (t[id].promise != 0) {
            t[id].val = t[id].promise * pref[rb - lb] % mod;
            if (lb + 1 < rb) {
                t[id * 2 + 1].promise = t[id].promise;
                t[id * 2 + 2].promise = t[id].promise;
            }
            t[id].promise = 0;
        }
    }

    void upd(int l, int r, int64_t x, int id, int lb, int rb) {
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
        t[id].val = (t[id * 2 + 1].val + p[m - lb] * t[id * 2 + 2].val % mod) % mod;
    }

    void upd(int l, int r, int64_t x) {
        upd(l, r, x, 0, 0, size);
    }

    int64_t get(int l, int r, int id, int lb, int rb) {
        push(id, lb, rb);
        if (l >= rb || r <= lb) return 0LL;
        if (l <= lb && rb <= r) return t[id].val;
        int m = (lb + rb) / 2;
        int64_t lhash = get(l, r, id * 2 + 1, lb, m);
        int64_t rhash = get(l, r, id * 2 + 2, m, rb);
        return (lhash + p[max(0, min(m - lb, m - l))] * rhash % mod) % mod;
    }

    int64_t get(int l, int r) {
        return get(l, r, 0, 0, size);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    for (int i = 1; i < maxn; i++) {
        p[i] = (p[i - 1] * fact) % mod;
        pref[i] = (pref[i - 1] + p[i - 1]) % mod;
    }
    int n; cin >> n;
    tree t(n);
    for (int i = 0; i < n; i++) {
        int64_t v; cin >> v;
        t.upd(i, i + 1, v);
    }
    int q; cin >> q;
    for (int i = 0, c, l, r, k; i < q; i++) {
        cin >> c >> l >> r >> k;
        if (c == 0) {
            t.upd(l - 1, r, k);
        } else {
            int64_t fhash = t.get(l - 1, l - 1 + k), shash = t.get(r - 1, r - 1 + k);
            cout << (fhash == shash ? '+' : '-');
        }
    }
    return 0;
}