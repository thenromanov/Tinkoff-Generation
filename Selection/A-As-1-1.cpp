#include <bits/stdc++.h>
using namespace std;

struct ft {
    int n;
    vector <int> t;

    ft(int n) {
        this->n = n;
        t.resize(n);
    }

    int sum(int r) {
        int res = 0;
        for (; r > 0; r -= r & -r) res += t[r];
        return res;
    }

    void add(int k, int x) {
        for (; k <= n; k += k & -k) t[k] += x;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    vector <pair <int, int>> coords(n);
    vector <int> x(n), y(n);
    vector <vector <int>> xs(1000007);
    int miny = INT_MAX, maxy = 0;
    ft l(1000001), r(1000001);
    for (int i = 0; i < n; i++) {
        cin >> coords[i].first >> coords[i].second;
        x[i] = coords[i].first;
        y[i] = coords[i].second;
    }
    sort(x.begin(), x.end());
    x.erase(unique(x.begin(), x.end()), x.end());
    sort(y.begin(), y.end());
    y.erase(unique(y.begin(), y.end()), y.end());
    for (int i = 0; i < n; i++) {
        coords[i].first = 2 * (lower_bound(x.begin(), x.end(), coords[i].first) - x.begin()) + 1;
        coords[i].second = 2 * (lower_bound(y.begin(), y.end(), coords[i].second) - y.begin()) + 1;
        miny = min(miny, coords[i].second);
        maxy = max(maxy, coords[i].second);
        r.add(coords[i].second, 1);
        xs[coords[i].first].push_back(coords[i].second);
    }
    int ans = INT_MAX, cntl = 0, cntr = n;
    for (int x = 0; x <= 1000000; x += 2) {
        if (x) {
            for (int u : xs[x - 1]) {
                l.add(u, 1);
                r.add(u, -1);
                cntl++, cntr--;
            }
        }
        int lft = miny / 2, rgh = (maxy + 1) / 2;
        while (lft + 3 < rgh) {
            int m1 = lft + (rgh - lft) / 3, m2 = rgh - (rgh - lft) / 3;
            int cntlm1 = l.sum(2 * m1), cntrm1 = r.sum(2 * m1);
            int cntlm2 = l.sum(2 * m2), cntrm2 = r.sum(2 * m2);
            int ans1 = max({cntlm1, cntl - cntlm1, cntrm1, cntr - cntrm1});
            int ans2 = max({cntlm2, cntl - cntlm2, cntrm2, cntr - cntrm2});
            if (ans1 < ans2) rgh = m2;
            else lft = m1;
        }
        int cntl1 = l.sum(2 * lft), cntr1 = r.sum(2 * lft);
        int cntl2 = l.sum(2 * lft + 2), cntr2 = r.sum(2 * lft + 2);
        int cntl3 = l.sum(2 * lft + 4), cntr3 = r.sum(2 * lft + 4);
        int ans1 = max({cntl1, cntl - cntl1, cntr1, cntr - cntr1});
        int ans2 = max({cntl2, cntl - cntl2, cntr2, cntr - cntr2});
        int ans3 = max({cntl3, cntl - cntl3, cntr3, cntr - cntr3});
        ans = min({ans, ans1, ans2, ans3});
    }
    cout << ans;
    return 0;
}