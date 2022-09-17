#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    for (int i = 0, v, u; i < n - 1; i++) cin >> v >> u;
    string s; cin >> s;
    vector <int> cnt(20);
    for (int i = 0; i < n; i++) cnt[s[i] - 'a']++;
    if (cnt[0] > 0 && cnt[1] > 0) cout << 2 << '\n';
    else cout << 1 << '\n';
    return 0;
}