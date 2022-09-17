#include <bits/stdc++.h>
using namespace std;

int64_t gcd(int64_t a, int64_t b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    if (a < b) swap(a, b);
    if (b == 0) return a;
    return gcd(b, a % b);
}

struct progression_tree {
    int size;
    vector <int64_t> t, promise;

    progression_tree(int n) {
        size = 1;
        while (size < n) size <<= 1;
        t.resize(2 * size + 1);
        promise.resize(2 * size + 1);
    }

    void push(int id, int lb, int rb) {
        if (promise[id] != 0) {
            t[id] += (rb - lb) * promise[id];
            if (lb + 1 < rb) {
                promise[2 * id + 1] += promise[id];
                promise[2 * id + 2] += promise[id];
            }
            promise[id] = 0;
        }
    }

    void build(vector <int64_t>& a, int id, int lb, int rb) {
        if (lb + 1 == rb) {
            t[id] = (lb < (int)a.size() ? a[lb] : 0);
            return;
        }
        int m = (lb + rb) / 2;
        build(a, id * 2 + 1, lb, m);
        build(a, id * 2 + 2, m, rb);
        t[id] = t[id * 2 + 1] + t[id * 2 + 2];
    }

    void build(vector <int64_t>& a) {
        build(a, 0, 0, size);
    }

    void update(int lq, int rq, int64_t k, int id, int lb, int rb) {
        push(id, lb, rb);
        if (rq <= lb || rb <= lq) return;
        if (lq <= lb && rb <= rq) {
            promise[id] += k;
            push(id, lb, rb);
            return;
        }
        int m = (lb + rb) / 2;
        update(lq, rq, k, id * 2 + 1, lb, m);
        update(lq, rq, k, id * 2 + 2, m, rb);
        t[id] = t[id * 2 + 1] + t[id * 2 + 2];
    }

    void update(int lq, int rq, int64_t k) {
        update(lq, rq, k, 0, 0, size);
    }

    int64_t get_member(int lq, int rq, int id, int lb, int rb) {
        push(id, lb, rb);
        if (rq <= lb || rb <= lq) return 0;
        if (lq <= lb && rb <= rq) return t[id];
        int m = (lb + rb) / 2;
        return get_member(lq, rq, id * 2 + 1, lb, m) + get_member(lq, rq, id * 2 + 2, m, rb);
    }

    int64_t get_member(int lq, int rq) {
        return get_member(lq, rq, 0, 0, size);
    }

    int64_t get_point(int k, int id, int lb, int rb) {
        push(id, lb, rb);
        if (lb + 1 == rb) return t[id];
        int m = (lb + rb) / 2;
        if (k < m) return get_point(k, id * 2 + 1, lb, m);
        else return get_point(k, id * 2 + 2, m, rb);
    }

    int64_t get_point(int k) {
        return get_point(k, 0, 0, size);
    }
};

struct gcd_tree {
    int size;
    vector <int64_t> t;

    gcd_tree(int n) {
        size = 1;
        while (size < n) size <<= 1;
        t.resize(2 * size - 1);
    }

    void build(vector <int64_t>& a, int id, int lb, int rb) {
        if (lb + 1 == rb) {
            t[id] = (lb < (int)a.size() ? a[lb] : 0);
            return;
        }
        int m = (lb + rb) / 2;
        build(a, id * 2 + 1, lb, m);
        build(a, id * 2 + 2, m, rb);
        t[id] = gcd(t[id * 2 + 1], t[id * 2 + 2]);
    }

    void build(vector <int64_t>& a) {
        build(a, 0, 0, size);
    }

    void add(int k, int64_t x, int id, int lb, int rb) {
        if (k >= rb || k < 2) return;
        if (lb + 1 == rb) {
            t[id] += x;
            return;
        }
        int m = (lb + rb) / 2;
        if (k < m) add(k, x, id * 2 + 1, lb, m);
        else add(k, x, id * 2 + 2, m, rb);
        t[id] = gcd(t[id * 2 + 1], t[id * 2 + 2]);
    }

    void add(int k, int64_t x) {
        add(k, x, 0, 0, size);
    }

    int64_t get(int lq, int rq, int id, int lb, int rb) {
        if (rq <= lb || rb <= lq) return 0;
        if (lq <= lb && rb <= rq) return t[id];
        int m = (lb + rb) / 2;
        return gcd(get(lq, rq, id * 2 + 1, lb, m), get(lq, rq, id * 2 + 2, m, rb));
    }

    int64_t get(int lq, int rq) {
        return get(lq, rq, 0, 0, size);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, q; cin >> n >> q;
    vector <int64_t> v(n), diff(n), ddiff(n);
    for (int64_t& u : v) cin >> u;
    for (int i = 0; i < n; i++) diff[i] = v[i] - (i == 0 ? 0 : v[i - 1]);
    for (int i = 2; i < n; i++) ddiff[i] = diff[i] - diff[i - 1];
    progression_tree ptree(n);
    ptree.build(diff);
    gcd_tree gtree(n);
    gtree.build(ddiff);
    for (int i = 0, c, l, r; i < q; i++) {
        cin >> c >> l >> r; l--, r--;
        if (c == 0) {
            int64_t a = ptree.get_member(0, l + 1), b = 0, c = 0;
            if (r - l + 1 >= 2) b = ptree.get_point(l + 1);
            if (r - l + 1 >= 3) c = gtree.get(l + 2, r + 1);
            cout << gcd(a, gcd(b, c)) << '\n';
        } else {
            int64_t k; cin >> k;
            ptree.update(l, r + 1, k);
            ptree.update(r + 1, r + 2, -k * (r - l + 1));
            gtree.add(l, k);
            gtree.add(r + 1, -k * (r - l + 2));
            gtree.add(r + 2, k * (r - l + 1));
        }
    }
    return 0;
}