#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3e5 + 7;

struct pt {
    int x, y;
};

struct query {
    pt f, s;
    int id;
};

struct ft {
    int n;
    vector <int> t;

    ft (int n) {
        this->n = n;
        t.resize(n);
    }

    int sum(int r) {
        int ans = 0;
        for (; r > 0; r -= r & -r) ans += t[r];
        return ans;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void inc(int k, int x) {
        for (; k <= n; k += k & -k) t[k] += x;
    }

    void fill_null() {
        t.assign(n, 0);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    vector <int> xs, ys;
    int n; cin >> n;
    vector <pt> pts(n);
    for (int i = 0, x, y; i < n; i++) {
        cin >> x >> y;
        pts[i] = {x, y};
        ys.push_back(y);
    }
    int m; cin >> m;
    vector <query> req(m);
    for (int i = 0, x1, y1, x2, y2; i < m; i++) {
        cin >> x1 >> y1 >> x2 >> y2;
        req[i] = {{x1, y1}, {x2, y2}, i};
        ys.push_back(y1), ys.push_back(y2);
    }
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    sort(pts.begin(), pts.end(), [](pt& a, pt& b){return (a.x == b.x ? a.y < b.y : a.x < b.x);});
    sort(req.begin(), req.end(), [](query& a, query& b){return (a.f.x < b.f.x);});
    int posf = 0, poss = 0;
    vector <pair <int, int>> ans(m);
    ft t(MAXN);
    for (auto q : req) {
        while (posf < n && pts[posf].x < q.f.x) t.inc(lower_bound(ys.begin(), ys.end(), pts[posf++].y) - ys.begin() + 1, 1);
        ans[q.id].first = t.sum(lower_bound(ys.begin(), ys.end(), q.f.y) - ys.begin() + 1, lower_bound(ys.begin(), ys.end(), q.s.y) - ys.begin() + 1);
    }
    t.fill_null();
    sort(req.begin(), req.end(), [](query& a, query& b){return (a.s.x < b.s.x);});
    for (auto q : req) {
        while (poss < n && pts[poss].x <= q.s.x) t.inc(lower_bound(ys.begin(), ys.end(), pts[poss++].y) - ys.begin() + 1, 1);
        ans[q.id].second = t.sum(lower_bound(ys.begin(), ys.end(), q.f.y) - ys.begin() + 1, lower_bound(ys.begin(), ys.end(), q.s.y) - ys.begin() + 1);
    }
    for (auto u : ans) cout << u.second - u.first << '\n';
    return 0;
}