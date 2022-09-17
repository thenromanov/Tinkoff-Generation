#include <bits/stdc++.h>
using namespace std;

mt19937 gena;

struct node {
    int p, size, val, min;
    node *l = nullptr, *r = nullptr;
    node(int v) : p(gena()), size(1), val(v), min(v) {}
};

int get_size(node *v) {return v ? v->size : 0;}
int get_min(node *v) {return v ? v->min : INT_MIN;}
void upd(node *v) {v->size = get_size(v->l) + get_size(v->r) + 1; v->min = min({get_min(v->l), get_min(v->r), v->val});}

pair <node*, node*> split(node *p, int k) {
    if (!p) return {nullptr, nullptr};
    if (get_size(p->l) + 1 <= k) {
        auto [l, r] = split(p->r, k - get_size(p->l) - 1);
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

node *merge(node *l, node *r) {
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

node *ctrlx(node *&p, int lq, int rq) {
    auto [t, r] = split(p, rq);
    auto [l, m] = split(t, lq);
    p = merge(l, r);
    return m;
}

void ctrlv(node *v, int k, node *&p) {
    auto [l, r] = split(p, k);
    p = merge(l, merge(v, r));
}



node *root = nullptr;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    vector <int> v = {1, 2, 3, 4, 5};
    for (int i = 0; i < v.size(); i++) {
        node *nd = new node(v[i]);
        ctrlv(nd, i, root);
    }
    cout << lower_bound(root, 2);
    return 0;
}