#include <bits/stdc++.h>
using namespace std;

int count_right(string& s) {
    int n = (int)s.size(), res = 0;
    for (int l = 1; l < n; l++) {
        if (l == 1) res += 9;
        else res += 90;
    }
    if (n == 1) res += s[0] - '0';
    else {
        res += (s[0] - '1') * 10 + (s[1] - '0');
        int a = s[1] - '0', d = (s[1] - s[0] + 10) % 10;
        bool good = true;
        for (int i = 2; i < n; i++) {
            a = (a + d) % 10;
            if (a != s[i] - '0') {
                if (a > s[i] - '0') good = false;
                break;
            }
        }
        res += good;
    }
    return res;
}

int count_left(string& s) {
    int n = (int)s.size(), res = 0, pos = n - 1;
    while (s[pos] == '0') s[pos--] = '9';
    s[pos]--;
    for (int l = 1; l < n; l++) {
        if (l == 1) res += 9;
        else res += 90;
    }
    if (n == 1) res += s[0] - '0';
    else {
        res += (s[0] - '1') * 10 + (s[1] - '0');
        int a = s[1] - '0', d = (s[1] - s[0] + 10) % 10;
        bool good = true;
        for (int i = 2; i < n; i++) {
            a = (a + d) % 10;
            if (a != s[i] - '0') {
                if (a > s[i] - '0') good = false;
                break;
            }
        }
        res += good;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string l, r; cin >> l >> r;
    cout << count_right(r) - count_left(l);
    return 0;
}