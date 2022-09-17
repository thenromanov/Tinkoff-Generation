#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 7;

struct ft {
    int n, logn;
    vector <int> tree;

    ft(int n) {
        this->n = n;
        logn = 1;
        while ((1 << logn) < n) logn++;
        tree.resize(n + 1);
    }

    int sum(int r) {
        int ans = 0;
        for (; r > 0; r -= r & -r) ans += tree[r];
        return ans;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void inc(int k, int x) {
        for (; k <= n; k += k & -k) tree[k] += x;
    }

    int lower_bound(int l, int r, int s) {
        s += sum(l - 1);
        int k = 0;
        for (int l = logn; l >= 0; l--) {
            if (k + (1 << l) <= r && tree[k + (1 << l)] < s) {
                k += (1 << l);
                s -= tree[k];
            }
        }
        return k;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ft tree(maxn);
    int n; cin >> n;
    for (int i = 1, v; i <= n; i++) {
        cin >> v;
        tree.inc(i, (v == 0));
    }
    int m; cin >> m;
    for (int i = 0; i < m; i++) {
        char c; cin >> c;
        if (c == 'u') {
            int k, x; cin >> k >> x;
            int cur = tree.sum(k, k);
            tree.inc(k, (x == 0) - cur);
        } else {
            int l, r, k; cin >> l >> r >> k;
            if (tree.sum(l, r) < k) {
                cout << -1 << '\n';
                continue;
            }
            cout << tree.lower_bound(l, r, k) + 1 << '\n';
        }
    }
    return 0;
}