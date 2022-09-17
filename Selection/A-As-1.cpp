#include <bits/stdc++.h>
using namespace std;

vector <pair <double, double>> coords;
double minx = 5e5, maxx = 0, miny = 5e5, maxy = 0;

int count(int x, int y) {
    int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0;
    for (auto u : coords) {
        if (u.first > x && u.second > y) cnt1++;
        else if (u.first > x && u.second < y) cnt2++;
        else if (u.first < x && u.second < y) cnt3++;
        else cnt4++;
    }
    return max({cnt1, cnt2, cnt3, cnt4});
}

int recy(int x) {
    int l = floor(miny), r = ceil(maxy);
    while (l + 3 < r) {
        int m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
        if (count(x, m1) < count(x, m2)) r = m2;
        else l = m1;
    }
    return min({count(x, l), count(x, l + 1), count(x, l + 2)});
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    coords.resize(n);
    vector <int> xs(n), ys(n);
    vector <pair <int, int>> cur(n);
    for (int i = 0; i < n; i++) {
        cin >> cur[i].first >> cur[i].second;
        xs[i] = cur[i].first;
        ys[i] = cur[i].second;
    }
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    for (int i = 0; i < n; i++) {
        coords[i].first = lower_bound(xs.begin(), xs.end(), cur[i].first) - xs.begin() + 0.5;
        coords[i].second = lower_bound(ys.begin(), ys.end(), cur[i].second) - ys.begin() + 0.5;
        minx = min(minx, coords[i].first);
        maxx = max(maxx, coords[i].first);
        miny = min(miny, coords[i].second);
        maxy = max(maxy, coords[i].second);
    }
    int l = floor(minx), r = ceil(maxx), ans = INT_MAX;
    while (l + 3 < r) {
        int m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
        if (recy(m1) < recy(m2)) r = m2;
        else l = m1;
    }
    ans = min({recy(l), recy(l + 1), recy(l + 2)});
    cout << ans;
    return 0;
}