#include <bits/stdc++.h>
using namespace std;

const int maxn = 524288;
// Ищем первое отрицательное


struct tree {
    struct node {
        int64_t max, promise;
    };

    int size;
    vector <node> t;

    tree(int n) {
        size = 1;
        while (size < n) size <<= 1;
        t.resize(2 * size - 1, {INT_MIN, 0});
    }

    void push(int id, int lb, int rb) {
        if (lb + 1 == rb) return;
        if (t[id].promise != 0) {
            t[id * 2 + 1].max += t[id].promise;
            t[id * 2 + 2].max += t[id].promise;
            t[id * 2 + 1].promise += t[id].promise;
            t[id * 2 + 2].promise += t[id].promise;
            t[id].promise = 0;
        }
    }

    void set(int k, int64_t x, int id, int lb, int rb) {
        push(id, lb, rb);
        if (lb + 1 == rb) {
            t[id].max = x;
            return;
        }
        int m = (lb + rb) / 2;
        if (k < m) set(k, x, id * 2 + 1, lb, m);
        else set(k, x, id * 2 + 2, m, rb);
        t[id].max = max(t[id * 2 + 1].max, t[id * 2 + 2].max);
    }

    void set(int k, int64_t x) {
        set(k, x, 0, 0, size);
    }

    void upd(int l, int r, int64_t x, int id, int lb, int rb) {
        push(id, lb, rb);
        if (l >= rb || r <= lb) return;
        if (l <= lb && rb <= r) {
            t[id].max += x;
            t[id].promise += x;
            push(id, lb, rb);
            return;
        }
        int m = (lb + rb) / 2;
        upd(l, r, x, id * 2 + 1, lb, m);
        upd(l, r, x, id * 2 + 2, m, rb);
        t[id].max = max(t[id * 2 + 1].max, t[id * 2 + 2].max);
    }

    void upd(int l, int r, int64_t x) {
        upd(l, r, x, 0, 0, size);
    }

    int get(int k, int id, int lb, int rb) {
        push(id, lb, rb);
        if (lb + 1 == rb) return lb;
        int m = (lb + rb) / 2;
        if (t[id * 2 + 2].max >= k) return get(k, id * 2 + 2, m, rb);
        else return get(k, id * 2 + 1, lb, m);
    }

    int get(int k) {
        return get(k, 0, 0, size);
    }
};

struct ft {
    int size;
    vector <int> t;

    ft(int n) {
        size = n;
        t.resize(size);
    }

    int sum(int r) {
        int ans = 0;
        for (; r > 0; r -= r & -r) ans += t[r];
        return ans;
    }

    void inc(int k, int x) {
        for (; k < size; k += k & -k) t[k] += x;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    tree stree(maxn);
    ft ftree(maxn);
    for (int i = 0; i < maxn; i++) stree.set(i, -i);
    ftree.inc(1, 1);
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        char c; int v; cin >> c >> v;
        if (c == '+') {
            stree.upd(v, maxn, 1);
            ftree.inc(v + 1, 1);
        } else {
            stree.upd(v, maxn, -1);
            ftree.inc(v + 1, -1);
        }
        int pos = stree.get(0);
        cout << ftree.sum(pos + 1) << '\n';
    }
    return 0;
}