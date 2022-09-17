#include <bits/stdc++.h>
using namespace std;

mt19937 gena;

struct node {
    int k, p, size;
    node *l = nullptr, *r = nullptr;
    node(int _k) : k(_k), p(gena()), size(1) {};
};

int get_size(node *p) {return p ? p->size : 0;}
void upd(node *p) {p->size = get_size(p->l) + get_size(p->r) + p->sum;}

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

pair <node*, node*> split(node *p, int k) {
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
    node *t = new node(k);
    p = merge(l, merge(t, r));
}

struct ft {
    int n;
    vector <node*> t;

    ft(int n) {
        this->n = n;
        t.resize(n + 1);
    }

    void inc(int k, int x) {
        for (; k <= n; k += k & -k) insert(t[k], x);
    }

    int sum(int r, int x) {
        int ans = 0;
        for (; r > 0; r -= r & -r) {
            auto [ll, rr] = split(t[r], x);
            ans += get_size(rr);
            t[r] = merge(ll, rr);
        }
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; 
    while (cin >> n) {
        ft tree(n);
        for (int i = 0, a, b; i < n; i++) {
            cin >> a >> b;
            tree.inc(a, b);
            cout << tree.sum(a, b) << ' ';
        }
        cout << '\n';
    }
    return 0;
}