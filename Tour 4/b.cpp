#include <bits/stdc++.h>
using namespace std;

struct pt {
    int x, a;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, k, l; cin >> n >> k >> l;
    vector <double> ans(k);
    vector <pt> stand, move;
    for (int i = 0; i < n; i++) {
        pt cur;
        cin >> cur.x >> cur.a;
        char c; cin >> c;
        if (c == 'D') {
            stand.push_back(cur);
            ans[cur.a] += l - cur.x;
        } else {
            move.push_back(cur);
        }
    }
    vector <int64_t> sum(k);
    int cur = -1, last = 0, psum = 0;
    for (int i = 0; i < move.size(); i++) {
        while (cur + 1 < stand.size() && stand[cur + 1].x < move[i].x) {
            cur++;
            vector <int64_t> ot(k);
            for (int j = 0; j < k; j++) ot[(j + stand[cur].a) % k] = sum[j];
            sum = ot;
            if (cur) {
                sum[stand[cur].a] += stand[cur].x - last;
            }
            psum = (psum + stand[cur].a) % k;
            last = stand[cur].x;
        }
        for (int j = 0; j < k; j++) ans[(move[i].a + j) % k] += (double)sum[j] / 2.0;
        if (cur >= 0) {
            ans[move[i].a] += (double)(move[i].x - last) / 2.0;
            ans[(move[i].a + psum) % k] += (double)(move[i].x + stand[0].x) / 2.0;
        } else {
            ans[move[i].a] += move[i].x;
        }
    }
    for (int i = 0; i < k; i++) cout << fixed << setprecision(10) << ans[i] << '\n';
    return 0;
}