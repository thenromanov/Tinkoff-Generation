#include "bits/stdc++.h"
using namespace std;

const int mod = 1e9;

struct node {
    int lb, rb, sum = 0;
    node *l = nullptr, *r = nullptr;

    node(int lb, int rb) : lb(lb), rb(rb) {
        if (lb + 1 < rb) {
            int m = (lb + rb) / 2;
            l = new node(lb, m);
            r = new node(m, rb);
        }
    }

    void add(int k, int x) {
        sum += x;
        if (l) {
            if (k < l->rb) {
                l = new node(*l);
                l->add(k, x);
            } else {
                r = new node(*r);
                r->add(k, x);
            }
        }
    }
};

vector <node*> roots;

void add(int k, int x) {
    node* root = new node(*roots.back());
    root->add(k, x);
    roots.push_back(root);
}

int kth(node *l, node *r, int k) {
    if (!l->l) return l->lb;
    if (r->l->sum - l->l->sum > k) return kth(l->l, r->l, k);
    return kth(l->r, r->r, k - r->l->sum + l->l->sum);
}

int query(int l, int r, int k) {
    return kth(roots[l - 1], roots[r], k);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    vector <int> v(n);
    int a, b; cin >> v[0] >> a >> b;
    for (int i = 1; i < n; i++) v[i] = (1LL * v[i - 1] * a + b) % mod;
    vector <int> cmpd = v;
    sort(cmpd.begin(), cmpd.end());
    cmpd.erase(unique(cmpd.begin(), cmpd.end()), cmpd.end());
    int size = 1;
    while (size < (int)cmpd.size()) size <<= 1;
    roots.push_back(new node(0, size));
    for (int i = 0; i < n; i++) add((int)(lower_bound(cmpd.begin(), cmpd.end(), v[i]) - cmpd.begin()), 1);
    cin >> b;
    int64_t ans = 0;
    for (int i = 0; i < b; i++) {
        int g, x, a1, b1, y, a2, b2, k, a3, b3;
        cin >> g >> x >> a1 >> b1 >> y >> a2 >> b2 >> k >> a3 >> b3; x--, y--, k--;
        for (int j = 0; j < g; j++) {
            int l = min(x, y), r = max(x, y);
            ans += cmpd[query(l + 1, r + 1, k)];       
            x = (1LL * x * a1 + b1) % n;
            y = (1LL * y * a2 + b2) % n;
            k = (1LL * k * a3 + b3) % (max(x, y) - min(x, y) + 1);
        }
    }
    cout << ans << '\n';
    return 0;
}