#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9 + 7;
const int maxn = 1e6 + 7;
const pair <int, int> bpair = {inf, inf};

vector <int> num_ops(maxn, -1);

int cnt_del(int n) {
    int cp = n, ans = 0;
    for (int j = 2; j * j <= n; j++) {
        if (num_ops[cp] != -1) {
            ans += num_ops[cp];
            cp = 1;
            break;
        }
        if (cp == 1) break;
        while (cp % j == 0) ans++, cp /= j;
    }
    if (cp != 1) ans++;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    vector <pair <int, int>> best(maxn, {inf, inf}), best2(maxn, {inf, inf});
    num_ops[1] = 0;
    int n; cin >> n;
    if (n == 1) {
        cout << 1 << '\n';
        return 0;
    }
    vector <int> a(n), ans(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        int j = 1;
        for (; j * j < a[i]; j++) {
            if (a[i] % j == 0) {
                if (num_ops[j] == -1) num_ops[j] = cnt_del(j);
                int s = a[i] / j;
                if (num_ops[s] == -1) num_ops[s] = cnt_del(s);
                if (best[j] == bpair) best[j] = {num_ops[a[i]] - num_ops[j], i};
                else {
                    pair <int, int> nval = {num_ops[a[i]] - num_ops[j], i};
                    if (best[j] > nval) {
                        if (best2[j] == bpair) best2[j] = best[j];
                        else best2[j] = min(best2[j], best[j]);
                        best[j] = nval;
                    } else {
                        if (best2[j] == bpair) best2[j] = nval;
                        else best2[j] = min(best2[j], nval);
                    }
                }
                if (s != 1) {
                    if (best[s] == bpair) best[s] = {num_ops[a[i]] - num_ops[s], i};
                    else {
                        pair <int, int> nval = {num_ops[a[i]] - num_ops[s], i};
                        if (best[s] > nval) {
                            if (best2[s] == bpair) best2[s] = best[s];
                            else best2[s] = min(best2[s], best[s]);
                            best[s] = nval;
                        } else {
                            if (best2[s] == bpair) best2[s] = nval;
                            else best2[s] = min(best2[s], nval);
                        }
                    }
                }
            }
        }
        if (j * j == a[i]) {
            if (best[j] == bpair) best[j] = {num_ops[a[i]] - num_ops[j], i};
            else {
                pair <int, int> nval = {num_ops[a[i]] - num_ops[j], i};
                if (best[j] > nval) {
                    if (best2[j] == bpair) best2[j] = best[j];
                    else best2[j] = min(best2[j], best[j]);
                    best[j] = nval;
                } else {
                    if (best2[j] == bpair) best2[j] = nval;
                    else best2[j] = min(best2[j], nval);
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        pair <int, int> res = {inf, inf};
        for (int j = 1; j * j <= a[i]; j++) {
            if (a[i] % j == 0) {
                pair <int, int> bst = best[j];
                if (bst.second == i) bst = best2[j];
                bst.first += num_ops[a[i]] - num_ops[j];
                if (bst < res) res = bst;
                int s = a[i] / j;
                bst = best[s];
                if (bst.second == i) bst = best2[s];
                }
                bst.first += num_ops[a[i]] - num_ops[s];
                if (bst < res) res = bst;
            }
        }
        ans[i] = res.second + 1;
    }
    for (int u : ans) cout << u << '\n';
    return 0;
}