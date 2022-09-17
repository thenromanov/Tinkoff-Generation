#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, x, y, k; cin >> n >> m >> x >> y >> k;
    if (k == 1) {
        cout << 0 << '\n';
        return 0;
    }
    if (k > n) {
        if (y == 1 || y == m) cout << k - 1 << '\n';
        else if (k == m) cout << k - 1 << '\n';
        else cout << k << '\n';
        return 0;
    }
    if (k > m) {
        if (x == 1 || x == n) cout << k - 1 << '\n';
        else if (k == n) cout << k - 1 << '\n';
        else cout << k << '\n';
        return 0;
    }
    if (x == 1 && y == 1) {
        cout << k << '\n';
        return 0;
    }
    if (x == 1 && y == m) {
        cout << k << '\n';
        return 0;
    }
    if (x == n && y == 1) {
        cout << k << '\n';
        return 0;
    }
    if (x == n && y == m) {
        cout << k << '\n';
        return 0;
    }
    if (x == 1 || x == n) {
        if (k == m) cout << k << '\n';
        else if (y + 1 - k <= 0 || y - 1 + k > m) cout << k << '\n';
        else cout << k + 1 << '\n';
        return 0;
    }
    if (y == 1 || y == m) {
        if (k == n) cout << k << '\n';
        else if (x + 1 - k <= 0 || x - 1 + k > n) cout << k << '\n';
        else cout << k + 1 << '\n';
        return 0;
    }
    if (k == n && k == m) {
        cout << k << '\n';
        return 0;
    }
    if (k == n) {
        if (y + 1 - k <= 0 || y - 1 + k > m) cout << k << '\n';
        else cout << k + 1 << '\n';
        return 0;
    }
    if (k == m) {
        if (x + 1 - k <= 0 || x - 1 + k > n) cout << k << '\n';
        else cout << k + 1 << '\n';
        return 0;
    }
    if (x + 1 - k <= 0 || x - 1 + k > n || y + 1 - k <= 0 || y - 1 + k > m) {
        cout << k + 1 << '\n';
        return 0;
    }
    cout << k + 2 << '\n';
    return 0;
}