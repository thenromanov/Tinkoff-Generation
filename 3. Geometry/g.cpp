#include <bits/stdc++.h>
using namespace std;

double eps = 1e-5;

struct point {
    double x, y;

    point() {};

    point(double x, double y) : x(x), y(y) {};

    bool operator== (const point& o) const {
        return abs(x - o.x) < eps && abs(y - o.y) < eps;
    }
};

struct circle {
	point c;
	double r;

    circle() {};

	circle(point p, double r): c(p), r(r) {};
};

double dist(const point& a, const point& b) {
	return hypot(a.x - b.x, a.y - b.y); 
}

struct line {
	double a, b, c;

    line() {};	
    
    line(point p, point v): a(-v.y), b(v.x), c(v.y * p.x - v.x * p.y){};
};

double det(double a, double b, double c, double d) {
	return a * d - b * c;
}

point intersect_line(const line& m, const line& n) {
	point res;
	double zn = det(m.a, m.b, n.a, n.b);
	res.x = -det(m.c, m.b, n.c, n.b) / zn;
	res.y = -det(m.a, m.c, n.a, n.c) / zn;
	return res;
}  

circle get_circle(const point& p1, const point& p2, const point& p3) {
	double a = dist(p1, p2);
	double b = dist(p3, p2);
	double c = dist(p1, p3);
	double p = (a + b + c) / 2;
	double r = a * b * c / (4 * sqrt(p * (p - a) * (p - b) * (p - c)));
	line l1, l2;
	l1.a = p1.x - p2.x;
	l1.b = p1.y - p2.y;
	l1.c = -l1.a * (p1.x + p2.x) / 2 - l1.b * (p1.y + p2.y) / 2;

	l2.a = p1.x - p3.x;
	l2.b = p1.y - p3.y;
	l2.c = -l2.a * (p1.x + p3.x) / 2 - l2.b * (p1.y + p3.y) / 2;

	point po = intersect_line(l1, l2);
	return circle(po, r);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << __lg(10);
    int n; cin >> n;
    if (n == 2) {
        cout << "1 1\n" << "1 2\n";
        return 0;
    }
    if (n == 3) {
        cout << "1 1\n" << "2 2 3\n";
        return 0;
    }
    if (n == 4) {
        cout << "2 1 2\n" << "2 3 4\n";
        return 0;
    }
    vector <point> points(n);
    for (int i = 0; i < n; i++) cin >> points[i].x >> points[i].y;
    vector <int> perm(5);
    iota(perm.begin(), perm.end(), 0);
    for (int i = 0; i < 120; i++) {
        circle c1 = get_circle(points[perm[0]], points[perm[1]], points[perm[2]]);
        vector <int> used(n), ans1, ans2;
        for (int j = 0; j < n; j++) {
            if (abs(dist(c1.c, points[j]) - c1.r) <= eps) {
                ans1.push_back(j);
                used[j] = true;
            }
        }
        int cnt = 0, pos = 0;
        vector <point> p(3, {0, 0});
        while (pos < n && cnt < 3) {
            if (!used[pos]) p[cnt++] = points[pos];
            pos++;
        }
        if (cnt < 3) {
			for (int j = 0; j < n; j++) {
				if (!used[j]) {
					ans2.push_back(j);
					used[j] = true;
				}
            }
			if (cnt == 0) ans2.push_back(0);
		} else {
			circle c2 = get_circle(p[0], p[1], p[2]);
			for (size_t j = 0; j < n; j++) {
				if (fabs(dist(c2.c, points[j]) - c2.r) <= eps) {
					ans2.push_back(j);
					used[j] = true;
				}
			}
		}
        bool f = true;
        for (int j = 0; j < n; j++) {
            if (!used[j]) f = false;
        }
        if (!f) {
            next_permutation(perm.begin(), perm.end());
            continue;
        }
        if (ans1.size() == n && ans2.size() == n) ans2.resize(1);
        cout << ans1.size() << ' ';
		for (int u : ans1) cout << u + 1 << ' '; 
        cout << '\n';
        cout << ans2.size() << ' ';
		for (int u : ans2) cout << u + 1 << ' ';
        cout << '\n';
		return 0;
    }
    return 0;
}