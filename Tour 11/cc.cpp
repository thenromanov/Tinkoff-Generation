#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-6;
const int64_t inf = 1e8;
int64_t curx;

struct event {
    int64_t x, y, r, s;

    bool operator< (const event& e) const {
        if (x + s * r != e.x + e.s * e.r) return x + s * r < e.x + e.s * e.r;
        if (y != e.y) return y < e.y;
        if (s != e.s) return s > e.s;
        return r > e.r;
    }
};

struct pt {
    int64_t x, y, r, s;

    double get(int64_t x0) const {
        return y + s * sqrt(1.0 * r * r - (x - x0) * (x - x0));
    }

    bool operator< (const pt& o) const {
        double v = get(curx), ov = o.get(curx);
        if (abs(v - ov) < eps) return v < ov;
        if (s != o.s) return s < o.s;
        return r > o.r;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    vector <event> events(2 * n);
    for (int i = 0; i < n; i++) {
        int64_t x, y, r; cin >> x >> y >> r;
        events[2 * i] = {x, y, r, -1};
        events[2 * i + 1] = {x, y, r, 1};
    }
    sort(events.begin(), events.end());
    set <pt> st;
    st.insert({0, -2 * inf, inf, 1});
    double ans = 0;
    for (auto e : events) {
        curx = e.x + e.r * e.s;
        if (e.s == -1) {
            auto it = st.lower_bound({e.x, e.y, e.r, -1});
            if (it->s == 1) {
                ans += e.r * e.r;
                st.insert({e.x, e.y, e.r, -1});
                st.insert({e.x, e.y, e.r, 1});
            }
        } else {
            st.erase({e.x, e.y, e.r, -1});
            st.erase({e.x, e.y, e.r, 1});
        }
    }
    cout << fixed << setprecision(10) << acos(-1) * ans << '\n';
    return 0;
}