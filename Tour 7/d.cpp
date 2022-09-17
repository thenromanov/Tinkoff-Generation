#include <bits/stdc++.h>
using namespace std;

const int maxn = 500 + 179;
const int maxk = 100 + 179;
const int64_t mod = 1e9 + 7;

int n, k;
vector <int> pxor(maxn);
vector <pair <int, int>> rng(maxk);

int64_t get_ans(int l, int i) {
    if (i + 1 == k) {
        if (l > n) return 0;
        int cur = pxor[n] ^ pxor[l - 1];
        return rng[i].first <= cur && cur <= rng[i].second;
    }
    int64_t res = 0;
    for (int j = l; j <= n; j++) {
        int cur = pxor[j] ^ pxor[l - 1];
        if (rng[i].first <= cur && cur <= rng[i].second) {
            res = (res + get_ans(j + 1, i + 1)) % mod;
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> pxor[i + 1];
        pxor[i + 1] ^= pxor[i];
    }
    for (int i = 0; i < k; i++) cin >> rng[i].first >> rng[i].second;
    cout << get_ans(1, 0);
    return 0;
}