#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    if (n == 1) {
        cout << 1 << '\n';
        return 0;
    }
    vector <int> a(n);
    for (int& u : a) cin >> u;
    vector <int> cntdel(n);
    for (int i = 0; i < n; i++) {
        int cp = a[i];
        for (int j = 2; j * j <= a[i]; j++) {
            if (cp == 1) break;
            while (cp % j == 0) {
                cntdel[i]++;
                cp /= j;
            }
        }
        if (cp != 1) cntdel[i]++;
    }
    for (int i = 0; i < n; i++) {
        vector <int> dist(n);
        dist[i] = INT_MAX;
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            int cp = __gcd(a[i], a[j]);
            int gc = cp;
            dist[j] = cntdel[i] + cntdel[j];
            for (int k = 2; k * k <= gc; k++) {
                if (cp == 1) break;
                while (cp % k == 0) {
                    dist[j] -= 2;
                    cp /= k;
                }
            }
            if (cp != 1) dist[j] -= 2;
        }
        cout << min_element(dist.begin(), dist.end()) - dist.begin() + 1 << '\n';
    }
    return 0;
}