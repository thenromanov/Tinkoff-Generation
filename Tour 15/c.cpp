#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int64_t k; cin >> k;
    int m; cin >> m;
    char c = 'b';
    cout << 'a';
    while (k) {
        int64_t n = 0;
        while (n * (n + 1) * (n + 2) / 6 <= k) n++;
        for (int i = 0; i < n - 1; i++) cout << 'a';
        k -= (n - 1) * n * (n + 1) / 6;
        cout << (c == 'c' ? c : c++);
    }
    return 0;
}