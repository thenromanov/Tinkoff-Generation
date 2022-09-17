#include <bits/stdc++.h>
using namespace std;

const int64_t inf = 1e18 + 1e9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int64_t n, a, b, c; cin >> n >> a >> b >> c;
    vector <vector <pair <int, int>>> g(a);
    for (int i = 0; i < a; i++) {
        g[i].push_back({(i + b) % a, b});
        g[i].push_back({(i + c) % a, c});
    }
    vector <int64_t> d(a, inf); d[1 % a] = 1;
    priority_queue <pair <int64_t, int>, vector <pair <int64_t, int>>, greater <pair <int64_t, int>>> q;
    q.push({1, 1 % a});
    while (!q.empty()) {
        int64_t curd = q.top().first;
        int v = q.top().second;
        q.pop();
        if (curd > d[v]) continue;
        for (auto [u, len] : g[v]) {
            if (d[u] > d[v] + len) {
                d[u] = d[v] + len;
                q.push({d[u], u});
            }
        }
    }
    int64_t ans = 0;
    for (int64_t i = 0; i < a; i++) {
        if (d[i] > n) continue;
        ans += ((n - i) / a - (d[i] - i) / a) + 1;
    }
    cout << ans << '\n';
    return 0;
}