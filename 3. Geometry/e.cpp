#include <bits/stdc++.h>
using namespace std;

typedef long double ld;

const ld eps = 1e-9;
const ld pi = acos(-1);

struct r {
    ld x, y;
    
    r () {};

    r (ld x, ld y) {
        this->x = x;
        this->y = y;
    }

    ld ang() {
        return atan2(y, x);
    }

    bool operator< (const r& p) const {return (x == p.x ? y < p.y : x < p.x);}
};

struct line {
    ld a, b, c;
};

r operator+ (r a, r b) {return r(a.x + b.x, a.y + b.y);};
r operator- (r a, r b) {return r(a.x - b.x, a.y - b.y);};
ld operator* (r a, r b) {return a.x * b.x + a.y * b.y;};
ld operator^ (r a, r b) {return a.x * b.y - a.y * b.x;};

int find_in_hull(int x, int y, vector <ld>& ha) {
    ld ang = atan2(y, x);
    if (ang < ha[0]) ang += 2 * pi;
    return (lower_bound(ha.begin(), ha.end(), ang) - ha.begin()) % ha.size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m; cin >> n >> m;
    vector <line> v(n);
    vector <r> p;
    set <r> used;
    for (auto& u : v) cin >> u.a >> u.b >> u.c;
    for (int i = 0; i < m; i++) {
        r cur; cin >> cur.x >> cur.y;
        if (used.find(cur) == used.end()) {
            p.push_back(cur);
            used.insert(cur);
        }
    }
    swap(p[0], *min_element(p.begin(), p.end()));
    sort(p.begin() + 1, p.end(), [&](const r& a, const r& b) {
        r v1 = a - p[0], v2 = b - p[0];
        return (v1 ^ v2) == 0 ? v1.x * v1.x + v1.y * v1.y < v2.x * v2.x + v2.y * v2.y : (v1 ^ v2) > 0;
    });
    vector <r> hull;
    for (auto pt : p) {
        while (hull.size() >= 2) {
            r nv = pt - hull.back();
            r lv = hull.back() - hull[hull.size() - 2];
            if ((nv ^ lv) > 0) hull.pop_back();
            else break;
        }
        hull.push_back(pt);
    }
    vector <ld> hullang;
    for (int i = 0; i < hull.size(); i++) {
        ld ang = (hull[(i + 1) % hull.size()] - hull[i]).ang();
        if (i && ang < hullang.back() - eps) ang += 2 * pi;
        hullang.push_back(ang); 
    }
    vector <int> ans;
    for (int i = 0; i < n; i++) {
        int p1 = find_in_hull(-v[i].b, v[i].a, hullang), p2 = find_in_hull(v[i].b, -v[i].a, hullang);
        ld dist1 = v[i].a * hull[p1].x + v[i].b * hull[p1].y + v[i].c;
        ld dist2 = v[i].a * hull[p2].x + v[i].b * hull[p2].y + v[i].c;
        if (dist1 * dist2 <= 0) ans.push_back(i + 1);
    }
    cout << ans.size() << '\n';
    for (auto u : ans) cout << u << ' ';
    return 0;
}