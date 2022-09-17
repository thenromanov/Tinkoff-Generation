#include <bits/stdc++.h>
using namespace std;

const int maxm = 1e5 + 7;
const int block = 400;
const int maxb = (maxm - 1) / block + 1;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, q; cin >> n >> m >> q;
    vector <map <int, int>> to(maxm);
    vector <map <int, int>> from(maxm);
    vector <vector <int>> by_block(maxb, vector <int> (n));
    for (int i = 0; i < maxb; i++) {
        for (int j = 0; j < n; j++) by_block[i][j] = j;
    }
    for (int i = 0; i < q; i++) {
        int t; cin >> t;
        if (t == 0) {
            int a, b, x; cin >> a >> b >> x; a--, b--, x--;
            if (to[x].find(a) == to[x].end()) {
                to[x][a] = a;
                from[x + 1][a] = a;
            }
            if (to[x].find(b) == to[x].end()) {
                to[x][b] = b;
                from[x + 1][b] = b;
            }
            swap(to[x][a], to[x][b]);
            swap(from[x + 1][to[x][a]], from[x + 1][to[x][b]]);
            int cura = a, curb = b;
            for (int i = x; i > x / block * block; i--) {
                if (from[i].find(cura) != from[i].end()) cura = from[i][cura];
                if (from[i].find(curb) != from[i].end()) curb = from[i][curb];
            }
            swap(by_block[x / block][cura], by_block[x / block][curb]);
        } else {
            int r, x, pos = 0; cin >> r >> x; r--, x--;
            while (x > (pos + 1) * block) {
                r = by_block[pos][r];
                pos++;
            }
            pos *= block;
            while (pos <= x) {
                if (to[pos].find(r) != to[pos].end()) r = to[pos][r];
                pos++;
            }
            cout << r + 1 << '\n';
        }
    }
    return 0;
}