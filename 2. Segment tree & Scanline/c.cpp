#include <bits/stdc++.h>
using namespace std;

const int INF = 1e6 + 7;

struct tree {
    struct node {
        int v, add, len;
    };

    int size;
    vector <node> t;

    tree(int n) {
        size = 1;
        while (size < n) size <<= 1;
        t.resize(2 * size - 1, {0, 0, 0});
    }
    
    void set(int k, int v, int len, int id, int lb, int rb) {
        if (lb + 1 == rb) {
            t[id].v = v;
            t[id].len = len;
            return;
        }
        int m = (lb + rb) / 2;
        if (k < m) set(k, v, len, id * 2 + 1, lb, m);
        else set(k, v, len, id * 2 + 2, m, rb);
        t[id].v = min(t[id * 2 + 1].v, t[id * 2 + 2].v);
        t[id].len = t[id * 2 + 1].len + t[id * 2 + 2].len;
    }

    void set(int k, int v, int len) {
        set(k, v, len, 0, 0, size);
    }

    void add(int l, int r, int x, int id, int lb, int rb) {
        if (l >= rb || r <= lb) return;
        if (l <= lb && rb <= r) {
            t[id].v += x;
            t[id].add += x;
            return;
        }
        int m = (lb + rb) / 2;
        add(l, r, x, id * 2 + 1, lb, m);
        add(l, r, x, id * 2 + 2, m, rb);
        if (t[id * 2 + 1].v == t[id * 2 + 2].v) {
            t[id].v = t[id * 2 + 1].v + t[id].add;
            t[id].len = t[id * 2 + 1].len + t[id * 2 + 2].len;
        } else {
            t[id].v = min(t[id * 2 + 1].v, t[id * 2 + 2].v) + t[id].add;
            t[id].len = (t[id * 2 + 1].v < t[id * 2 + 2].v ? t[id * 2 + 1].len : t[id * 2 + 2].len);
        }
    }

    void add(int l, int r, int x) {
        add(l, r, x, 0, 0, size);
    }

    pair <int, int> get(int l, int r, int id, int lb, int rb) {
        if (l >= rb || r <= lb) return {INF, t[id].len};
        if (l <= lb && rb <= r) return {t[id].v, t[id].len};
        int m = (lb + rb) / 2;
        pair <int, int> m1 = get(l, r, id * 2 + 1, lb, m);
        pair <int, int> m2 = get(l, r, id * 2 + 2, m, rb);
        if (m1.first == m2.first) return {m1.first + t[id].add, m1.second + m2.second};
        return (m1.first < m2.first ? make_pair(m1.first + t[id].add, m1.second) : make_pair(m2.first + t[id].add, m2.second));
    }

    pair <int, int> get(int l, int r) {
        return get(l, r, 0, 0, size);
    }
};

struct pt {
    int x, y;
};

struct line {
    bool open;
    int x, ly, ry;

    line(bool open, int x, int ly, int ry) {
        this->open = open;
        this->x = x;
        this->ly = ly;
        this->ry = ry;
    }

    bool operator< (const line& l) const {
        if (x == l.x) return open < l.open;
        return x < l.x;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    vector <pair <pt, pt>> coords(n);
    vector <int> ys;
    for (int i = 0, x1, y1, x2, y2; i < n; i++) {
        cin >> x1 >> y1 >> x2 >> y2;
        coords[i] = {{x1, y1}, {x2, y2}};
        ys.push_back(y1), ys.push_back(y2);
    }
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    tree t(ys.size());
    for (int i = 0; i < (int)ys.size() - 1; i++) t.set(i, 0, ys[i + 1] - ys[i]);
    vector <line> scanline;
    for (auto u : coords) {
        scanline.push_back(line(true, u.first.x, lower_bound(ys.begin(), ys.end(), u.first.y) - ys.begin(), lower_bound(ys.begin(), ys.end(), u.second.y) - ys.begin()));
        scanline.push_back(line(false, u.second.x, lower_bound(ys.begin(), ys.end(), u.first.y) - ys.begin(), lower_bound(ys.begin(), ys.end(), u.second.y) - ys.begin()));
    }
    sort(scanline.begin(), scanline.end());
    int64_t ans = 0;
    int lastx = (scanline.size() > 0 ? scanline[0].x : 0);
    for (auto l : scanline) {
        if (l.x != lastx) {
            pair <int, int64_t> res = t.get(0, ys.size() - 1);
            if (res.first > 0) res.second = 0LL;
            ans += 1LL * (l.x - lastx) * (ys.back() - ys.front() - res.second);
        }
        if (l.open) t.add(l.ly, l.ry, 1);
        else t.add(l.ly, l.ry, -1);
        lastx = l.x;
    }
    cout << ans << '\n';
    return 0;
}