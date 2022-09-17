#include <bits/stdc++.h>
using namespace std;

const int maxn = 1 << 18;
const int logn = 18;

struct node {
    node *l = nullptr, *r = nullptr;
    int sum = 0;

    node() {};
    node(int sum) : sum(sum) {};
    node(node *l, node *r) : l(l), r(r), sum(l->sum + r->sum) {};
};

vector <vector <node*>> base(2, vector <node*> (logn + 1));
node *onehp;

struct p {
    node *t = onehp;
    int attack = 0, health = maxn - 1, death = -1;

    p() {};
};

node* update(int lq, int rq, int c, node *t, int lb, int rb) {
    if (rq <= lb || rb <= lq) return t;
    if (lq <= lb && rb <= rq) return base[c][__lg(rb - lb)];
    int m = (lb + rb) / 2;
    return new node(update(lq, rq, c, t->l, lb, m), update(lq, rq, c, t->r, m, rb));
}

int lower_bound(int k, node *t, int lb, int rb) {
    if (k >= rb || t->sum == 0) return maxn;
    if (lb + 1 == rb) return lb;
    int m = (lb + rb) / 2;
    int res = lower_bound(k, t->l, lb, m);
    if (res == maxn) res = lower_bound(k, t->r, m, rb);
    return res;
}

void fight(p& c, int a) {
    a += c.health;
    int p = lower_bound(a, c.t, 0, maxn);
    if (p == maxn) c.t = update(0, maxn, 0, c.t, 0, maxn);
    else {
        c.t = update(p, p + 1, 0, c.t, 0, maxn);
        if (a < p) c.t = update(a, p, 1, c.t, 0, maxn);
    }
}

bool is_dead(p& c) {
    return lower_bound(0, c.t, 0, maxn) == maxn;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    for (int b = 0; b < 2; b++) {
        node *cur = new node(b);
        for (int i = 0; i <= logn; i++) {
            base[b][i] = cur;
            cur = new node(cur, cur);
        }
    }
    onehp = update(maxn - 1, maxn, 1, base[0][logn], 0, maxn);
    vector <p> c;
    int n; cin >> n;
    for (int i = 0, t; i < n; i++) {
        cin >> t;
        if (t == 1) {
            c.push_back(p());
        } else if (t == 2) {
            int id; cin >> id; id--;
            if (!is_dead(c[id])) c[id].attack++;
        } else if (t == 3) {
            int id; cin >> id; id--;
            if (!is_dead(c[id])) c[id].health--;
        } else if (t == 4) {
            int id; cin >> id; id--;
            c.push_back(c[id]);
            if (c.back().death != -1) c.back().death = i + 1;
        } else {
            int x, y; cin >> x >> y; x--, y--;
            if (!is_dead(c[x]) && !is_dead(c[y])) {
                fight(c[x], c[y].attack);
                fight(c[y], c[x].attack);
                if (is_dead(c[x])) c[x].death = i + 1;
                if (is_dead(c[y])) c[y].death = i + 1;
            }
        }
    }
    cout << c.size() << '\n';
    for (auto u : c) cout << u.death << ' ';
    return 0;
}