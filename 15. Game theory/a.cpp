#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    if (n == 1 || n == 3) cout << "Ivan Urgant\nDraw\n";
    else if (n == 2) cout << "Ivan Safonov\n";
    else if (n == 4) cout << "Ivan Urgant\nMix\n";
    else if (n % 2) cout << "Ivan Safonov\n";
    else cout << "Ivan Urgant\nDraw\n";
    return 0;
}