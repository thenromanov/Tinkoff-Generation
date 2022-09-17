#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 7;

struct tree {
    int size;
    vector <int> t;

    tree(int n) {
        size = 1;
        while (size < n) size <<= 1;
        t.resize(2 * size - 1, -1);
    }

    void set(int k, int x, int id, int lb, int rb) {
        if (lb + 1 == rb) {
            t[id] = x;
            return;
        }
        int m = (lb + rb) / 2;
        if (k < m) set(k, x, id * 2 + 1, lb, m);
        else set(k, x, id * 2 + 2, m, rb);
        t[id] = max(t[id * 2 + 1], t[id * 2 + 2]);
    }

    void set(int k, int x) {
        set(k, x, 0, 0, size);
    }

    int get(int k, int id, int lb, int rb) {
        if (lb + 1 == rb) return lb;
        int m = (lb + rb) / 2;
        if (t[id * 2 + 1] >= k) return get(k, id * 2 + 1, lb, m);
        else return get(k, id * 2 + 2, m, rb);
    }

    int get(int k) {
        return get(k, 0, 0, size);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    tree t(MAXN);
    for (int i = 0; i < MAXN; i++) t.set(i, i);
    for (int i = 0, c; i < n; i++) {
        cin >> c;
        if (c > 0) {
            int pos = t.get(c - 1);
            cout << pos + 1 << '\n';
            t.set(pos, -1);
        } else {
            t.set(abs(c) - 1, abs(c) - 1);
        }
    }
    return 0;
}