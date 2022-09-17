#include <bits/stdc++.h>
using namespace std;

struct tree {
    struct node {
        int max, add;
    };
    
    int size = 1;
    vector <node> t;

    tree(int n) {
        while (size < n) size <<= 1;
        t.resize(2 * size - 1, {0, 0});
    }

    void set(int k, int v, int id, int lb, int rb) {
        if (lb + 1 == rb) {
            t[id].max = v;
            return;
        }
        int m = (lb + rb) / 2;
        if (k < m) set(k, v, id * 2 + 1, lb, m);
        else set(k, v, id * 2 + 2, m, rb);
        t[id].max = max(t[id * 2 + 1].max, t[id * 2 + 2].max);
    }

    void set(int k, int v) {
        set(k, v, 0, 0, size);
    }

    void add(int l, int r, int x, int id, int lb, int rb) {
        if (l >= rb || r <= lb) return;
        if (l <= lb && rb <= r) {
            t[id].add += x;
            t[id].max += x;
            return;
        }
        int m = (lb + rb) / 2;
        add(l, r, x, id * 2 + 1, lb, m);
        add(l, r, x, id * 2 + 2, m, rb);
        t[id].max = max(t[id * 2 + 1].max, t[id * 2 + 2].max) + t[id].add;
    }

    void add(int l, int r, int x) {
        add(l, r, x, 0, 0, size);
    }

    int get(int l, int r, int id, int lb, int rb) {
        if (l >= rb || r <= lb) {
            return INT_MIN;
        }
        if (l <= lb && rb <= r) {
            return t[id].max;
        }
        int m = (lb + rb) / 2;
        return max(get(l, r, id * 2 + 1, lb, m), get(l, r, id * 2 + 2, m, rb)) + t[id].add;
    }

    int get(int l, int r) {
        return get(l, r, 0, 0, size);
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    tree t(n + 1);
    vector <int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        v[i] = n - v[i] - 1;
        t.set(i, -i);
    }
    t.set(n, -n);
    int i = 0;
    for (; i < n; i++) {
        t.add(v[i] + 1, n + 1, 1);
        int res = t.get(v[i] + 1, i + 2);
        if (res >= 0) break;
    }
    cout << n - i - 1;
    return 0;
}