#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    vector <int> lp(n + 1), pr;
    for (int i = 2; i <= n; i++) {
        if (lp[i] == 0) {
            pr.push_back(i);
            lp[i] = i;
        }
        for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && 1LL * i * pr[j] <= n; j++) lp[i * pr[j]] = pr[j];
    }
    vector <int> phi(n + 1);
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if ((i / lp[i]) % lp[i] == 0) phi[i] = phi[i / lp[i]] * lp[i];
        else phi[i] = phi[i / lp[i]] * (lp[i] - 1);
    }
    for (int i = 2; i <= n; i++) {
        int cnt = 0;
        int j = 1;
        for (j = 1; j * j < n; j++) cnt += 2 * (n % j == 0);
        if (j * j == n) cnt++;
        cout << cnt + phi[i] << ' ';
    }
    return 0;
}