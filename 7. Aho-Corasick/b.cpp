#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string s, t; cin >> s >> t;
    int n = (int)s.size(), m = (int)t.size();
    vector <int> a(n, -1), b(m, -1);
    map <char, int> lpos;
    for (int i = 0; i < n; i++) {
        if (lpos.find(s[i]) == lpos.end()) a[i] = i + 1;
        else a[i] = i - lpos[s[i]];
        lpos[s[i]] = i;
    }
    lpos.clear();
    for (int i = 0; i < m; i++) {
        if (lpos.find(t[i]) == lpos.end()) b[i] = -i - 1;
        else b[i] = i - lpos[t[i]];
        lpos[t[i]] = i;
    }
    vector <int> p(m);
    int cur = 0;
    for (int i = 1; i < m; i++) {
        while (cur > 0 && !(b[i] == b[cur] || (b[i] < 0 && b[cur] < 0) || (b[cur] < 0 && b[i] >= -b[cur]))) cur = p[cur - 1];
        if (b[i] == b[cur] || (b[i] < 0 && b[cur] < 0) || (b[cur] < 0 && b[i] >= -b[cur])) cur++;
        p[i] = cur;
    }
    vector <int> ans;
    cur = 0;
    for (int i = 0; i < n; i++) {
        while (cur > 0 && !(a[i] == b[cur] || (b[cur] < 0 && a[i] >= - b[cur]))) cur = p[cur - 1];
        if (a[i] == b[cur] || (b[cur] < 0 && a[i] >= -b[cur])) cur++;
        if (cur == m) ans.push_back(i - m + 2), cur = p[cur - 1];
    }
    cout << ans.size() << '\n';
    for (int u : ans) cout << u << ' ';
    return 0;
}