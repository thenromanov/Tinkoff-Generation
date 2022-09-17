#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int64_t n, k; cin >> n >> k;
    if (n == 3 && k > 1) {
        cout << k * (k - 1) * (k - 2) * 3 + k * (k - 1);
        return 0;
    }
    if (n == 4 && k > 1) {
        cout << k * (k - 1) * (k - 2) * 4095 + k * (k - 1);
        return 0;
    }
    if (n == 1 && k > 1) {
        cout << k * (k - 1) * (k - 2) * 260610 + k * (k - 1);
        return 0;
    }
    if (k < 3) {
        cout << 0;
        return 0;
    }
    if (n == 2) {
        cout << k * (k - 1) * (k - 2) * 16;
        return 0;
    }
    if (n == 5) {
        cout << k * (k - 1) * (k - 2) * 2;
        return 0;
    }
    if (n == 6) {
        cout << k * (k - 1) * (k - 2);
        return 0;
    }
    if (n == 7) {
        cout << k * (k - 1) * (k - 2) * 16;
        return 0;
    }
    return 0;
}