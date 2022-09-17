#include <bits/stdc++.h>
using namespace std;

struct rec {
    int64_t w, h;
};

struct line {
    int64_t k, b;

    line(int64_t k, int64_t b) {
        this->k = k;
        this->b = b;
    }

    int64_t get(int64_t x) {
        return k * x + b;
    }
};

struct CHT {
    vector <line> hull;

    CHT() {}

    bool comp(line c, line p, line n) {
        return (c.b - n.b) * (c.k - p.k) <= (p.b - c.b) * (n.k - c.k);
    }

    void add_line(line l) {
        while (hull.size() >= 2 && comp(hull[hull.size() - 1], hull[hull.size() - 2], l)) hull.pop_back();
        hull.push_back(l);
    }

    int64_t query(int64_t x) {
        int l = -1, r = hull.size() - 1;
        while (l + 1 < r) {
            int m = (l + r) / 2;
            if (hull[m].get(x) >= hull[m + 1].get(x)) l = m;
            else r = m;
        }
        return hull[r].get(x);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    vector <rec> v(n), recs;
    for (auto& u : v) cin >> u.w >> u.h;
    sort(v.begin(), v.end(), [](const rec& a, const rec& b) {return a.h == b.h ? a.w > b.w : a.h > b.h;});
    int64_t maxw = 0;
    recs.push_back({0, 1000000007});
    for (int i = 0; i < n; i++) {
        if (v[i].w <= maxw) continue;
        maxw = v[i].w;
        recs.push_back(v[i]);
    }
    n = (int)recs.size();
    vector <int64_t> dp(n);
    CHT hull;
    for (int i = 1; i < n; i++) {
        hull.add_line(line(recs[i].h, dp[i - 1]));
        dp[i] = hull.query(recs[i].w);
    }
    cout << dp[n - 1];
    return 0;
}