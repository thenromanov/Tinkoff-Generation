#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e6;

int INDEX = 1;

struct node {
    int l, r, min = 0;
};

struct req {
    int l, s, x;

    bool operator< (const req& o) const {
        return l < o.l;
    }
};

node t[maxn];
vector <int> roots = {0};

void build(int id, int lb, int rb) {
    if (lb + 1 == rb) return;
    int m = (lb + rb) / 2;
    t[id].l = INDEX++, t[id].r = INDEX++;
    build(t[id].l, lb, m);
    build(t[id].r, m, rb);
}

int upd(int k, int x, int id, int lb, int rb) {
    int ID = INDEX++;
    t[ID] = t[id];
    if (lb + 1 == rb) {
        t[ID].min = x;
        return ID;
    }
    int m = (lb + rb) / 2;
    if (k < m) t[ID].l = upd(k, x, t[ID].l, lb, m);
    else t[ID].r = upd(k, x, t[ID].r, m, rb);
    t[ID].min = min(t[t[ID].l].min, t[t[ID].r].min);
    return ID;
}

int get(int k, int id, int lb, int rb) {
    if (lb + 1 == rb) return lb;
    int m = (lb + rb) / 2;
    if (t[t[id].l].min <= k) return get(k, t[id].l, lb, m);
    return get(k, t[id].r, m, rb);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, s, m; cin >> n >> s >> m;
    int size = 1;
    while (size < s + 1) size <<= 1;
    build(roots.back(), 0, size);
    vector <pair <int, pair <int, int>>> q;
    for (int i = 0, s, l, r; i < m; i++) {
        cin >> s >> l >> r; s--, l--, r--;
        q.push_back({l, {INT_MAX, s}});
        q.push_back({r, {r, s}});
    }
    sort(q.begin(), q.end());
    for (auto u : q) roots.push_back(upd(u.second.second, u.second.first, roots.back(), 0, size));
    int t, p = 0; cin >> t;
    for (int i = 0, x, y; i < t; i++) {
        cin >> x >> y; x--, y--;
        pair <int, pair <int, int>> h = {y + p, {INT_MAX - 1, INT_MAX}};
        int r = upper_bound(q.begin(), q.end(), h) - q.begin();
        p = get(x + p, roots[r], 0, size);
        if (p >= s) p = 0;
        else p++;
        cout << p << '\n';
    }
    return 0;
}