#include <bits/stdc++.h>
using namespace std;

struct r {
    int64_t x, y;
    r () {};
    r (int64_t x, int64_t y) {
        this->x = x;
        this->y = y;
    }
};

istream& operator>> (istream& in, r& pt) {
    in >> pt.x >> pt.y;
    return in;
}

r operator+ (r a, r b) {return r(a.x + b.x, a.y + b.y);};
r operator- (r a, r b) {return r(a.x - b.x, a.y - b.y);};
int64_t operator^ (r a, r b) {return a.x * b.y - a.y * b.x;};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, k, cnt = 0; cin >> n >> m >> k;
    vector <r> pts(n);
    for (auto& u : pts) cin >> u;
    for (int i = 0; i < m; i++) {
        r q; cin >> q;
        if ((((pts[n - 1] - pts[0]) ^ (q - pts[n - 1])) > 0) || (((pts[1] - pts[0]) ^ (q - pts[1])) < 0)) continue;
        int lft = 1, rgh = n - 1;
        while (lft + 1 < rgh) {
            int mid = (lft + rgh) / 2;
            if (((pts[mid] - pts[0]) ^ (q - pts[mid])) >= 0) lft = mid;
            else rgh = mid;
        }
        if (((pts[rgh] - pts[lft]) ^ (q - pts[rgh])) >= 0) cnt++;
    }
    cout << (cnt >= k ? "YES\n" : "NO\n");
    return 0;
}