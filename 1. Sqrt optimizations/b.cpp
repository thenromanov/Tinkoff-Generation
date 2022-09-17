#include <bits/stdc++.h>
using namespace std;

const int K = 316;
int n, m, pos = 0;
struct query {int l, r, x, y;};
vector <query> buffer;

vector <vector <int>> v;
vector <query> ord;

vector <int> rebuild() {
    vector <int> r1(n + 2), r2(n + 2);
    for (query q : buffer) {
        r1[q.l] += q.x;
        r1[q.r + 1] -= q.x;
        r2[q.l + 1] += q.y;
        r2[q.r + 1] -= q.y * (q.r - q.l + 1);
        r2[q.r + 2] += q.y * (q.r - q.l);
        ord.push_back(q);
    }
    for (int i = 2; i < n; i++) r2[i] += r2[i - 1];
    for (int i = 1; i < n; i++) r1[i] += r2[i];
    for (int i = 1; i < n; i++) r1[i] += r1[i - 1];
    buffer.clear();
    return r1;
}

void upd(int l, int r, int x, int y) {
    buffer.push_back({l, r, x, y});
    if (buffer.size() == K) {
        v.push_back(rebuild());
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n;
    vector <int> a(n), b(n), need(n);
    for (int& u : a) cin >> u;
    for (int& u : b) cin >> u;
    for (int i = 0; i < n; i++) need[i] = b[i] - a[i];
    cin >> m;
    for (int i = 0, l, r, x, y; i < m; i++) {
        cin >> l >> r >> x >> y;
        upd(l - 1, r - 1, x, y);
    }
    if (buffer.size()) v.push_back(rebuild());
    int cnt = (int)v.size();
    for (int i = 0; i < n; i++) {
        if (need[i] <= 0) {
            cout << 0 << ' ';
            continue;
        }
        int pos = 0, j = 0;
        int psum = 0;
        for (; pos < cnt; pos++) {
            psum += v[pos][i];
            if (psum >= need[i]) break;
        }
        if (pos == cnt) {
            cout << -1 << ' ';
            continue;
        }
        j = pos * K;
        int cur = 0;
        for (; j < min(m, pos * K + K); j++) {
            if (i >= ord[j].l && i <= ord[j].r) {
                cur += ord[j].x + ord[j].y * (i - ord[j].l);
            }
            if (psum - v[pos][i] + cur >= need[i]) break;
        }
        cout << j + 1 << ' ';
    }
    return 0;
}