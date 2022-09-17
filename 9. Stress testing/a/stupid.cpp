#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    while (n--) {
        int a, c1 = 1, c2 = 1; cin >> a;
        while (c2 < a) {
            int c3 = c1 + c2;
            c1 = c2, c2 = c3;
        }
        cout << (c2 == a ? "Yes\n" : "No\n");
    }
    return 0;
}