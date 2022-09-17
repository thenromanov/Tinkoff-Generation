#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string s1, s2; cin >> s1 >> s2;
    vector <int> v1, v2;
    for (auto u : s1) v1.push_back(u - '0');
    for (auto u : s2) v2.push_back(u - '0');
    int i = 0, j = 0, cur = 0;
    for (; i < (int)v1.size() && j < (int)v2.size(); i++) {
        cur = (cur + v1[i]) % 10;
        if (cur == v2[j]) {
            cur = 0;
            j++;
        }
    }
    if (j < (int)v2.size()) {
        cout << "NO\n";
        return 0;
    }
    cur = 0;
    for (; i < (int)v1.size(); i++) cur = (cur + v1[i]) % 10;
    cout << (cur == 0 ? "YES\n" : "NO\n");
    return 0;
}