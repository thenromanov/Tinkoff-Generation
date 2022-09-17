#include <bits/stdc++.h>
using namespace std;

mt19937 gena;

struct node {
    int64_t k, p, sum;
    node *l = nullptr, *r = nullptr;
    node(int64_t _k) : k(_k), p(gena()), sum(_k) {};
};

int64_t get_sum(node *p) {return p ? p->sum : 0LL;}
void upd(node *p) {p->sum = get_sum(p->l) + get_sum(p->r) + p->k;}

node* merge(node *l, node *r) {
    if (!l) return r;
    if (!r) return l;
    if (l->p > r->p) {
        l->r = merge(l->r, r);
        upd(l);
        return l;
    } else {
        r->l = merge(l, r->l);
        upd(r);
        return r;
    }
}

pair <node*, node*> split(node* p, int k) {
    if (!p) return {nullptr, nullptr};
    if (p->k <= k) {
        auto [l, r] = split(p->r, k);
        p->r = l;
        upd(p);
        return {p, r};
    } else {
        auto [l, r] = split(p->l, k);
        p->l = r;
        upd(p);
        return {l, p};
    }
}

void insert(node *&p, int k) {
    auto [l, r] = split(p, k);
    node* t = new node(k);
    p = merge(l, merge(t, r));
}

struct ft {
    int n;
    vector <node*> t;

    ft(int n) {
        this->n = n;
        t.resize(n + 1);
    }

    void inc(int k, int64_t x) {
        for (; k <= n; k += k & -k) insert(t[k], x);
    }

    int64_t get(int r, int mx) {
        int64_t ans = 0;
        for (; r > 0; r -= r & -r) {
            auto [ll, rr] = split(t[r], mx);
            ans += get_sum(ll);
            t[r] = merge(ll, rr);
        }
        return ans;
    }

    int64_t get(int l, int r, int mx) {
        return get(r, mx) - get(l - 1, mx);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m; cin >> n >> m;
    ft tree(150179);
    for (int i = 1, k; i <= n; i++) {
        cin >> k;
        tree.inc(i, k);
    }
    for (int i = 0, l, r; i < m; i++) {
        cin >> l >> r;
        int64_t cursum = 0LL, maxsum = 0LL;
        while (true) {
            cursum = tree.get(l, r, maxsum + 1);
            if (cursum == maxsum) break;
            maxsum = cursum;
        }
        cout << maxsum + 1 << '\n';
    }
    return 0;
}