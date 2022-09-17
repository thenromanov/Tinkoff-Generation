#include <bits/stdc++.h>
using namespace std;

struct node {
    int64_t lb, rb, size;
    node *l = nullptr, *r = nullptr;
    vector <bool> promise;

    node(int64_t lb, int64_t rb) {
        this->lb = lb;
        this->rb = rb;
        size = rb - lb;
    }

    void extend() {
        if (!l) {
            int64_t m = (lb + rb) / 2;
            l = new node(lb, m);
            r = new node(m, rb);
        }
    }

    void insert(bool f) {
        if (size == 0) return;
        if (!(size == 1 && f == 0)) promise.push_back(f);
        size = (size + f) / 2;
    }

    void push() {
        extend();
        for (auto u : promise) {
            r->insert(u ^ (l->size % 2));
            l->insert(u);
        }
        promise.clear();
    }

    void update(int64_t lx, int64_t rx) {
        if (size <= lx || rx <= 0) return;
        if (lx <= 1 && size <= rx) {
            this->insert((rx % 2) ^ 1);
            return;
        }
        push();
        r->update(lx - l->size, rx - l->size);
        l->update(lx, rx);
        size = l->size + r->size;
    }

    int64_t get(int64_t x) {
        push();
        if (lb + 1 == rb) return lb;
        if (l->size > x) return l->get(x);
        else return r->get(x - l->size);
    }
};



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int64_t n, m; cin >> n >> m;
    node tree(0, m);
    for (int i = 0; i < n; i++) {
        int64_t l, r; cin >> l >> r;
        cout << tree.get(l - 1) + 1 << ' ' << tree.get(r - 1) + 1 << '\n';
        tree.update(l - 1, r);
    }
    return 0;
}