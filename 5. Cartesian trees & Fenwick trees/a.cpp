#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 7;

struct tree {
    struct node {
        vector <int> values;
    };

    int size;
    vector <node> t;

    tree(int n) {
        size = 1;
        while (size < n) size <<= 1;
        t.resize(2 * size - 1);
    }

    void build(vector <int>& a, int id, int lb, int rb) {
        if (lb + 1 == rb) {
            if (lb < a.size()) t[id].values.push_back(a[lb]);
            return;
        }
        int m = (lb + rb) / 2;
        build(a, id * 2 + 1, lb, m);
        build(a, id * 2 + 2, m, rb);
        t[id].values.resize((int)t[id * 2 + 1].values.size() + (int)t[id * 2 + 2].values.size());
        merge(t[id * 2 + 1].values.begin(), t[id * 2 + 1].values.end(), t[id * 2 + 2].values.begin(), t[id * 2 + 2].values.end(), t[id].values.begin());
    }

    void build(vector <int>& a) {
        build(a, 0, 0, size);
    }

    int get(int l, int r, int mn, int mx, int id, int lb, int rb) {
        if (l >= rb || r <= lb) return 0;
        if (l <= lb && rb <= r) return (int)(upper_bound(t[id].values.begin(), t[id].values.end(), mx) - t[id].values.begin()) - (int)(lower_bound(t[id].values.begin(), t[id].values.end(), mn) - t[id].values.begin());
        int m = (lb + rb) / 2;
        return get(l, r, mn, mx, id * 2 + 1, lb, m) + get(l, r, mn, mx, id * 2 + 2, m, rb);
    }

    int get(int l, int r, int mn, int mx) {
        return get(l, r, mn, mx, 0, 0, size);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    tree stree(maxn);
    int n, m; cin >> n >> m;
    vector <int> a(n);
    for (int& u : a) cin >> u;
    stree.build(a);
    for (int i = 0, l, r, mn, mx; i < m; i++) {
        cin >> l >> r >> mn >> mx;
        cout << stree.get(l - 1, r, mn, mx) << '\n';
    }
    return 0;
}