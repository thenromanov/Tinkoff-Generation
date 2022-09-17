#include <bits/stdc++.h>
using namespace std;

struct r {
    int x, y;

    r() {};
    r(int x, int y) : x(x), y(y) {};
};

r operator+(const r& a, const r& b) { return r(a.x + b.x, a.y + b.y); }
r operator-(const r& a, const r& b) { return r(a.x - b.x, a.y - b.y); }
r operator*(const r& a, double k) { return r(a.x * k, a.y * k); }
int64_t operator*(const r& a, const r& b) { return a.x * b.x + a.y * b.y; }
int64_t operator^(const r& a, const r& b) { return a.x * b.y - a.y * b.x; }

bool one_line(const r& a, const r& b, const r& c) {
    r v1 = b - a, v2 = c - b, v3 = a - c;
    return ((v1 ^ v2) == 0 && (v2 ^ v3) == 0 && (v1 ^ v3) == 0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    vector <r> pts(n);
    pair <r, pair <int, pair <int, int>>> right = {{INT_MIN, INT_MIN}, {-1, {-1, -1}}}, up = {{INT_MIN, INT_MIN}, {-1, {-1, -1}}};
    for (int i = 0; i < n; i++) cin >> pts[i].x >> pts[i].y, pts[i].x *= 2, pts[i].y *= 2;
    for (int i = 0; i < n; i++) {
        if (pts[i].x >= 0 && pts[i].y >= 0) {
            if (pts[i].y >= 0 && pts[i].x > right.first.x) right = {pts[i], {i, {-1, -1}}};
            if (pts[i].x >= 0 && pts[i].y > up.first.y && right.second.first != i) up = {pts[i], {i, {-1, -1}}};
        }
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            for (int k = j + 1; k < n; k++) {
                if (k == i || one_line(pts[i], pts[j], pts[k])) continue;
                r v = pts[k] - pts[j];
                r mid = pts[j] + (v * 0.5);
                v = mid - pts[i];
                r e = pts[i] + (v * 2);
                if (e.y >= 0 && e.x > right.first.x) right = {e, {i, {j, k}}};
                if (e.x >= 0 && e.y > up.first.y && right.second.first != i) up = {e, {i, {j, k}}};
            }
        }
    }
    if (right.first.x < 0 || right.first.y < 0 || up.first.x < 0 || up.first.y < 0 || right.second.first == -1 || up.second.first == -1) {
        cout << "-1\n";
        return 0;
    }
    vector <vector <int>> ans;
    if (right.second.second.first != -1) ans.push_back({right.second.second.first, right.second.second.second, right.second.first});
    if (up.second.second.first != -1) ans.push_back({up.second.second.first, up.second.second.second, up.second.first});
    for (int i = 0; i < n; i++) {
        if (i == right.second.first || i == up.second.first) continue;
        if (pts[i].x >= 0 && pts[i].y >= 0) continue;
        if (one_line(pts[i], right.first, up.first)) {
            cout << "-1\n";
            return 0;
        }
        r v = right.first - up.first;
        r mid = up.first + (v * 0.5);
        v = mid - pts[i];
        r e = pts[i] + (v * 2);
        if (e.x < 0 || e.y < 0) {
            cout << "-1\n";
            return 0;
        }
        ans.push_back({right.second.first, up.second.first, i});
    }
    cout << ans.size() << '\n';
    for (auto u : ans) cout << u[0] + 1 << ' ' << u[1] + 1 << ' ' << u[2] + 1 << '\n';
    return 0;
}