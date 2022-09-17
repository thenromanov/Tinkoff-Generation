#include <bits/stdc++.h>
using namespace std;

struct tree {
    struct node {
        vector <int64_t> values, psum;
    };

    int size;
    vector <node> t;

    tree(int n) {
        size = 1;
        while (size < n) size <<= 1;
        t.resize(2 * size - 1);
    }

    void build(vector <int64_t>& a, int id, int lb, int rb) {
        if (lb + 1 == rb) {
            if (lb < (int)a.size()) {
                t[id].values.push_back(a[lb]);
                t[id].psum.push_back(a[lb]);
            }
            return;
        }
        int m = (lb + rb) / 2;
        build(a, id * 2 + 1, lb, m);
        build(a, id * 2 + 2, m, rb);
        t[id].values.resize((int)t[id * 2 + 1].values.size() + (int)t[id * 2 + 2].values.size());
        t[id].psum.resize((int)t[id * 2 + 1].values.size() + (int)t[id * 2 + 2].values.size());
        merge(t[id * 2 + 1].values.begin(), t[id * 2 + 1].values.end(), t[id * 2 + 2].values.begin(), t[id * 2 + 2].values.end(), t[id].values.begin());
        for (int i = 0; i < (int)t[id].psum.size(); i++) {
            t[id].psum[i] = t[id].values[i];
            if (i) t[id].psum[i] += t[id].psum[i - 1];
        }
    }

    void build(vector <int64_t>& a) {
        build(a, 0, 0, size);
    }

    int64_t get(int l, int r, int64_t mn, int64_t mx, int id, int lb, int rb) {
        if (l >= rb || r <= lb) return 0;
        if (l <= lb && rb <= r) {
            int posl = upper_bound(t[id].values.begin(), t[id].values.end(), mn) - t[id].values.begin();
            int posr = upper_bound(t[id].values.begin(), t[id].values.end(), mx) - t[id].values.begin();
            int64_t ans = 0;
            if (posr) ans += t[id].psum[posr - 1];
            if (posl) ans -= t[id].psum[posl - 1];
            return ans;
        }
        int m = (lb + rb) / 2;
        return get(l, r, mn, mx, id * 2 + 1, lb, m) + get(l, r, mn, mx, id * 2 + 2, m, rb);
    }

    int64_t get(int l, int r, int64_t mn, int64_t mx) {
        return get(l, r, mn, mx, 0, 0, size);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m; cin >> n >> m;
    tree stree(n);
    vector <int64_t> a(n);
    for (auto& u : a) cin >> u;
    stree.build(a);
    for (int i = 0, l, r; i < m; i++) {
        cin >> l >> r;
        int64_t maxcost = 0LL, maxsum = 0LL, cursum = 0LL;
        while (true) {
            cursum = stree.get(l - 1, r, maxcost, maxsum + 1);
            if (cursum == 0LL) break;
            maxcost = maxsum + 1;
            maxsum += cursum;
        }
        cout << maxsum + 1 << '\n';
    }
    return 0;
}