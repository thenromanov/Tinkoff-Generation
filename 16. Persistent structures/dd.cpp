#include "bits/stdc++.h"
using namespace std;

const int maxn = 11000000;
const int mod = 1e9;

int INDEX = 1;

struct node {
    int l, r, sum = 0;
};

vector <node> t(maxn);
vector <int> roots = {0};

void build(int id, int lb, int rb) {
    if (lb + 1 == rb) return;
    int m = (lb + rb) / 2;
    t[id].l = INDEX++, t[id].r = INDEX++;
    build(t[id].l, lb, m);
    build(t[id].r, m, rb);
}

void add(int k, int x, int id, int lb, int rb) {
    t[id].sum += x;
    if (lb + 1 == rb) return;
    int m = (lb + rb) / 2;
    if (k < m) {
        t[INDEX] = t[t[id].l];
        t[id].l = INDEX++;
        add(k, x, t[id].l, lb, m);
    } else {
        t[INDEX] = t[t[id].r];
        t[id].r = INDEX++;
        add(k, x, t[id].r, m, rb);
    }
}

void update(int k, int x, int lb, int rb) {
    int id = INDEX++;
    t[id] = t[roots.back()];
    add(k, x, id, lb, rb);
    roots.push_back(id);
}

int kth(int l, int r, int k, int lb, int rb) {
    if (lb + 1 == rb) return lb;
    int m = (lb + rb) / 2;
    if (t[t[r].l].sum - t[t[l].l].sum > k) return kth(t[l].l, t[r].l, k, lb, m);
    return kth(t[l].r, t[r].r, k - t[t[r].l].sum + t[t[l].l].sum, m, rb);
}

int query(int l, int r, int k, int lb, int rb) {
    return kth(roots[l - 1], roots[r], k, lb, rb);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    vector <int> v(n);
    int a, b; cin >> v[0] >> a >> b;
    for (int i = 1; i < n; i++) v[i] = ((int64_t)v[i - 1] * a + b) % mod;
    vector <int> cmpd = v;
    sort(cmpd.begin(), cmpd.end());
    cmpd.erase(unique(cmpd.begin(), cmpd.end()), cmpd.end());
    int size = 1;
    while (size < (int)cmpd.size()) size <<= 1;
    build(roots[0], 0, size);
    for (int i = 0; i < n; i++) update((int)(lower_bound(cmpd.begin(), cmpd.end(), v[i]) - cmpd.begin()), 1, 0, size);
    cin >> b;
    int64_t ans = 0;
    for (int i = 0; i < b; i++) {
        int g, x, a1, b1, y, a2, b2, k, a3, b3;
        cin >> g >> x >> a1 >> b1 >> y >> a2 >> b2 >> k >> a3 >> b3; x--, y--, k--;
        for (int j = 0; j < g; j++) {
            int l = min(x, y), r = max(x, y);
            ans += cmpd[query(l + 1, r + 1, k, 0, size)];
            x = ((int64_t)l * a1 + b1) % n;
            y = ((int64_t)r * a2 + b2) % n;
            k = ((int64_t)k * a3 + b3) % (max(x, y) - min(x, y) + 1);
        }
    }
    cout << ans << '\n';
    return 0;
}