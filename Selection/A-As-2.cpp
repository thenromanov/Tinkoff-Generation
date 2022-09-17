#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 7;
vector <int> p(MAXN), s(MAXN);

int find(int v) {
    if (v == p[v]) return v;
    return p[v] = find(p[v]);
}

void unite(int v, int u) {
    v = find(v), u = find(u);
    if (s[v] > s[u]) swap(v, u);
    s[u] += s[v];
    p[v] = u;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    vector <vector <int>> onx(n), ony(n), g;
    for (int i = 0, x, y; i < n; i++) {
        cin >> x >> y;
        onx[i] = {x, y, i};
        ony[i] = {y, x, i};
        p[i] = i;
        s[i] = 1;
    }
    sort(onx.begin(), onx.end());
    sort(ony.begin(), ony.end());
    for (int i = 1; i < n; i++) {
        g.push_back({min(abs(onx[i][0] - onx[i - 1][0]), abs(onx[i][1] - onx[i - 1][1])), onx[i - 1][2], onx[i][2]});
        g.push_back({min(abs(ony[i][0] - ony[i - 1][0]), abs(ony[i][1] - ony[i - 1][1])), ony[i - 1][2], ony[i][2]});
    }
    sort(g.begin(), g.end());
    int64_t ans = 0;
    for (auto u : g) {
        int len = u[0], a = u[1], b = u[2];
        if (find(a) != find(b)) {
            unite(a, b);
            ans += len;
        }
    }
    cout << ans;
    return 0;
}