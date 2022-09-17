#include <bits/stdc++.h>
using namespace std;

typedef long double ld;

const ld eps = 1e-7;
const ld pi = acos(-1);

struct r {
    ld x, y;
    r () {};
    r (ld x, ld y) {
        this->x = x;
        this->y = y;
    }

    ld len() {
        return hypot(x, y);
    }

    bool operator== (const r& p) const {return abs(x - p.x) < eps && abs(y - p.y) < eps;};
    bool operator!= (const r& p) const {return abs(x - p.x) > eps || abs(y - p.y) > eps;};
};

istream& operator>> (istream& in, r& p) {
    in >> p.x >> p.y;
    return in;
}

r operator+ (r a, r b) {return r(a.x + b.x, a.y + b.y);};
r operator- (r a, r b) {return r(a.x - b.x, a.y - b.y);};
r operator* (r a, ld k) {return r(a.x * k, a.y * k);};
r operator* (ld k, r a) {return r(a.x * k, a.y * k);};
ld operator* (r a, r b) {return a.x * b.x + a.y * b.y;};
ld operator^ (r a, r b) {return a.x * b.y - a.y * b.x;};

pair <r, r> intersect(r p, r m, ld rad) {
    ld h = (p - m).len() * (p - m).len();
    ld rad2 = sqrt(h - rad * rad);
    ld a = -2 * p.x, b = -2 * p.y, c = p.x * p.x + p.y * p.y + rad * rad - rad2 * rad2;
    r pt(-a * c / (a * a + b * b), -b * c / (a * a + b * b));
    ld d = rad * rad - c * c / (a * a + b * b);
    ld mult = sqrt(d / (a * a + b * b));
    r pt1 = pt + r(b * mult, -a * mult), pt2 = pt + r(-b * mult, a * mult);
    return {pt1, pt2};
}

ld len(r p1, r p2, r pc, ld rad) {
    r v1 = p1 - pc, v2 = p2 - pc;
    return abs(atan2(v1 ^ v2, v1 * v2)) * rad;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(10);
    r p1, p2, pc; cin >> p1 >> p2 >> pc;
    ld rad; cin >> rad;
    if (p1 == p2) {
        cout << 0 << '\n';
        return 0;
    }
    r mod = pc;
    p1 = p1 - mod;
    p2 = p2 - mod;
    pc = pc - mod;
    if (p1.x * p1.x + p1.y * p1.y == rad * rad && p2.x * p2.x + p2.y * p2.y == rad * rad) {
        cout << len(p1, p2, pc, rad) << '\n';
        return 0;
    }
    ld a = p2.y - p1.y, b = p1.x - p2.x, c = -a * p1.x - b * p1.y;
    r pt(-a * c / (a * a + b * b), -b * c / (a * a + b * b));
    if (c * c > rad * rad * (a * a + b * b) + eps) {
        cout << (p2 - p1).len() << '\n';
    } else if (abs(c * c - rad * rad * (a * a + b * b)) < eps) {
        cout << (p2 - p1).len() << '\n';
    } else {
        ld d = rad * rad - c * c / (a * a + b * b);
        ld mult = sqrt(d / (a * a + b * b));
        r pt1 = pt + r(b * mult, -a * mult), pt2 = pt + r(-b * mult, a * mult);
        if ((p1 - pt1) * (p2 - pt1) >= 0 && (p1 - pt2) * (p2 - pt2) >= 0) {
            cout << (p2 - p1).len() << '\n';
            return 0;
        }
        pair <r, r> f = intersect(p1, pc, rad), s = intersect(p2, pc, rad);
        ld ans = len(f.first, s.first, pc, rad) + min((f.first - p1).len() + (s.first - p2).len(), (f.first - p2).len() + (s.first - p1).len());
        ans = min(ans, len(f.second, s.first, pc, rad) + min((f.second - p1).len() + (s.first - p2).len(), (f.second - p2).len() + (s.first - p1).len()));
        ans = min(ans, len(f.first, s.second, pc, rad) + min((f.first - p1).len() + (s.second - p2).len(), (f.first - p2).len() + (s.second - p1).len()));
        ans = min(ans, len(f.second, s.second, pc, rad) + min((f.second - p1).len() + (s.second - p2).len(), (f.second - p2).len() + (s.second - p1).len()));
        cout << ans << '\n';
    }
    return 0;
}