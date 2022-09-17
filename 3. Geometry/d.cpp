#include <bits/stdc++.h>
using namespace std;

typedef long double ld;

const ld eps = 1e-6;


struct r {
    ld x, y;
    r () {};
    r (ld x, ld y) {
        this->x = x;
        this->y = y;
    }

    bool operator== (r& other) {
        return x == other.x && y == other.y;
    }
};

struct circle {
    r center;
    ld rad;
};

istream& operator>> (istream& in, r& p) {
    in >> p.x >> p.y;
    return in;
}

ostream& operator<< (ostream& out, r& p) {
    out << p.x << ' ' << p.y;
    return out;
}

istream& operator>> (istream& in, circle& c) {
    in >> c.center >> c.rad;
    return in;
}

r operator+ (r a, r b) {return r(a.x + b.x, a.y + b.y);};
r operator- (r a, r b) {return r(a.x - b.x, a.y - b.y);};
r operator* (r a, ld k) {return r(a.x * k, a.y * k);};
r operator* (ld k, r a) {return r(a.x * k, a.y * k);};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(16);
    circle f, s; cin >> f >> s;
    if (f.rad <= 0 || s.rad <= 0) {
        cout << 0 << '\n';
        return 0;
    }
    if (f.center == s.center) {
        if (f.rad == s.rad) cout << 3 << '\n';
        else cout << 0 << '\n';
        return 0;
    }
    r modifier = -1 * f.center;
    f.center = f.center + modifier;
    s.center = s.center + modifier;
    ld a = -2 * s.center.x, b = -2 * s.center.y, c = s.center.x * s.center.x + s.center.y * s.center.y + f.rad * f.rad - s.rad * s.rad;
    r pt(-a * c / (a * a + b * b), -b * c / (a * a + b * b));
    if (c * c > f.rad * f.rad * (a * a + b * b) + eps) {
        cout << 0 << '\n';
    } else if (abs(c * c - f.rad * f.rad * (a * a + b * b)) < eps) {
        cout << 1 << '\n';
        pt = pt + (-1 * modifier);
        cout << pt << '\n';
    } else {
        ld d = f.rad * f.rad - c * c / (a * a + b * b);
        ld mult = sqrt(d / (a * a + b * b));
        r pt1 = pt + r(b * mult, -a * mult) + (-1 * modifier), pt2 = pt + r(-b * mult, a * mult) + (-1 * modifier);
        cout << 2 << '\n';
        cout << pt1 << '\n' << pt2 << '\n';
    }
    return 0;
}