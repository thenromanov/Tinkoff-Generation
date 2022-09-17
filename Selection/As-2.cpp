#include <bits/stdc++.h>
using namespace std;

const int MAXN = 46, MAXABLE = 25;
vector <int64_t> fib(MAXN);
vector <vector <int64_t>> cnt;

void fill(int n) {
    for (int i = 0; i < fib[n]; i++) {
        if (i < fib[n - 2]) cnt[n][i] = cnt[n - 2][i];
        else cnt[n][i] = cnt[n - 2][fib[n - 2] - 1] + cnt[n - 1][i - fib[n - 2]];
    }
}

int64_t get(int n, int k) {
    if (n < MAXABLE) return cnt[n][k];
    if (k < fib[n - 2]) return get(n - 2, k);
    return get(n - 2, fib[n - 2] - 1) + get(n - 1, k - fib[n - 2]); 
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    fib[0] = fib[1] = 1;
    for (int i = 2; i < MAXN; i++) fib[i] = fib[i - 2] + fib[i - 1];
    cnt.resize(MAXABLE);
    for (int i = 0; i < MAXABLE; i++) cnt[i].resize(fib[i]);
    cnt[0][0] = 1;
    for (int i = 2; i < MAXABLE; i++) fill(i);
    int q; cin >> q;
    while (q--) {
        int64_t n, k; cin >> n >> k;
        cout << get(n, k - 1) << '\n';
    }
    return 0;
}