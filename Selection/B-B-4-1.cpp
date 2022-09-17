#include <bits/stdc++.h>
using namespace std;

struct tree {

    struct node {
        int64_t size;
        int min, add;
    };
    
    int size = 1;
    vector <node> t;

    tree(int n) {
        while (size < n) size <<= 1;
        t.resize(2 * size - 1, {0, 0, 0});
    }

    void set_size(int k, int v, int64_t x, int id, int lb, int rb) {
        if (lb + 1 == rb) {
            t[id].min = v;
            t[id].size = x;
            return;
        }
        int m = (lb + rb) / 2;
        if (k < m) set_size(k, v, x, id * 2 + 1, lb, m);
        else set_size(k, v, x, id * 2 + 2, m, rb);
        t[id].min = min(t[id * 2 + 1].min, t[id * 2 + 2].min);
        t[id].size = t[id * 2 + 1].size + t[id * 2 + 2].size;
    }

    void set_size(int k, int v, int64_t x) {
        set_size(k, v, x, 0, 0, size);
    }

    void add(int l, int r, int x, int id, int lb, int rb) {
        if (l >= rb || r <= lb) return;
        if (l <= lb && rb <= r) {
            t[id].add += x;
            t[id].min += x;
            return;
        }
        int m = (lb + rb) / 2;
        add(l, r, x, id * 2 + 1, lb, m);
        add(l, r, x, id * 2 + 2, m, rb);
        if (t[id * 2 + 1].min == t[id * 2 + 2].min) {
            t[id].min = t[id * 2 + 1].min + t[id].add;
            t[id].size = t[id * 2 + 1].size + t[id * 2 + 2].size;
        } else {
            t[id].min = min(t[id * 2 + 1].min, t[id * 2 + 2].min) + t[id].add;
            t[id].size = (t[id * 2 + 1].min < t[id * 2 + 2].min ? t[id * 2 + 1].size : t[id * 2 + 2].size);
        }
    }

    void add(int l, int r, int x) {
        add(l, r, x, 0, 0, size);
    }

    pair <int, int64_t> get(int l, int r, int id, int lb, int rb) {
        if (l >= rb || r <= lb) {
            return make_pair(1e5, t[id].size);
        }
        if (l <= lb && rb <= r) {
            return make_pair(t[id].min, t[id].size);
        }
        int m = (lb + rb) / 2;
        pair <int, int64_t> m1 = get(l, r, id * 2 + 1, lb, m);
        pair <int, int64_t> m2 = get(l, r, id * 2 + 2, m, rb);
        if (m1.first == m2.first) return make_pair(m1.first + t[id].add, m1.second + m2.second);
        return (m1.first < m2.first ? make_pair(m1.first + t[id].add, m1.second) : make_pair(m2.first + t[id].add, m2.second));
    }

    pair <int, int64_t> get(int l, int r) {
        return get(l, r, 0, 0, size);
    }
};

struct line {
    bool open;
    int64_t x, ly, ry;

    bool operator < (const line& l) const {
        if (x == l.x) return open < l.open;
        return x < l.x;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int64_t n1, m1; cin >> n1 >> m1;
    string v1; cin >> v1;
    int64_t n2, m2; cin >> n2 >> m2;
    string v2; cin >> v2;
    int64_t a = n1 * n2 / gcd(n1, n2), b = m1 * m2 / gcd(m1, m2);
    int64_t x1 = a / n1, y1 = b / m1, x2 = a / n2, y2 = b / m2;
    vector <int64_t> cmpy;
    for (int i = 0; i <= m1; i++) cmpy.push_back(y1 * i);
    for (int i = 0; i <= m2; i++) cmpy.push_back(y2 * i);
    sort(cmpy.begin(), cmpy.end());
    cmpy.erase(unique(cmpy.begin(), cmpy.end()), cmpy.end());
    vector <line> zero, one;
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m1; j++) {
            int ly = lower_bound(cmpy.begin(), cmpy.end(), y1 * j) - cmpy.begin(), ry = lower_bound(cmpy.begin(), cmpy.end(), y1 * (j + 1)) - cmpy.begin();
            if (v1[i * m1 + j] == '0') zero.push_back({true, x1 * i, ly, ry}), zero.push_back({false, x1 * (i + 1), ly, ry});
            else one.push_back({true, x1 * i, ly, ry}), one.push_back({false, x1 * (i + 1), ly, ry});
        }
    }
    for (int i = 0; i < n2; i++) {
        for (int j = 0; j < m2; j++) {
            int ly = lower_bound(cmpy.begin(), cmpy.end(), y2 * j) - cmpy.begin(), ry = lower_bound(cmpy.begin(), cmpy.end(), y2 * (j + 1)) - cmpy.begin();
            if (v2[i * m2 + j] == '0') zero.push_back({true, x2 * i, ly, ry}), zero.push_back({false, x2 * (i + 1), ly, ry});
            else one.push_back({true, x2 * i, ly, ry}), one.push_back({false, x2 * (i + 1), ly, ry});

        }
    }
    sort(zero.begin(), zero.end());
    sort(one.begin(), one.end());
    tree t(cmpy.size() - 1);
    for (int i = 0; i < cmpy.size() - 1; i++) t.set_size(i, 0, cmpy[i + 1] - cmpy[i]);
    int64_t a0 = 0, a1 = 0, lastx = 0;
    for (auto l : zero) {
        if (l.x != lastx) {
            pair <int, int64_t> res = t.get(0, cmpy.size() - 1);
            if (res.first > 0) res.second = 0;
            a0 += (l.x - lastx) * (b - res.second);
        }
        if (l.open) t.add(l.ly, l.ry, 1);
        else t.add(l.ly, l.ry, -1);
        lastx = l.x;
    }
    for (int i = 0; i < cmpy.size() - 1; i++) t.set_size(i, 0, cmpy[i + 1] - cmpy[i]);
    lastx = 0;
    for (auto l : one) {
        if (l.x != lastx) {
            pair <int, int64_t> res = t.get(0, cmpy.size() - 1);
            if (res.first > 0) res.second = 0;
            a1 += (l.x - lastx) * (b - res.second);
        }
        if (l.open) t.add(l.ly, l.ry, 1);
        else t.add(l.ly, l.ry, -1);
        lastx = l.x;
    }
    cout << 2 * a * b - a0 - a1;
    return 0;
}