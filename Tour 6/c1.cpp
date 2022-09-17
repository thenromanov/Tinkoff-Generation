#include <bits/stdc++.h>
using namespace std;

int solve(const string& a, const string& b) {
    string s = a + "#" + b;
    int n = (int)s.size(), asz = (int)a.size();
    vector <vector <int>> pfuncs(asz + 1, vector <int> (n));
    for (int i = 0; i <= asz; i++) {
        for (int j = i + 1; j < n; j++) {
            int cur = pfuncs[i][j - 1];
            while (s[j] != s[cur + i] && cur > 0) cur = pfuncs[i][cur + i - 1];
            if (s[j] == s[cur + i]) pfuncs[i][j] = cur + 1;
        }
    }
    int ans = 0;
    for (int i = 0; i <= asz; i++) {
        for (int j = asz + 1; j < n; j++) {
            ans = max(ans, pfuncs[i][j] + pfuncs[i + pfuncs[i][j]][j - pfuncs[i][j]]);
        }
    }
    return ans;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string a, b; cin >> a >> b;
    if ((int)a.size() > (int)b.size()) swap(a, b);
    int ans = 0;
    ans = max(ans, solve(a, b));
    reverse(b.begin(), b.end());
    ans = max(ans, solve(a, b));
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    ans = max(ans, solve(a, b));
    reverse(b.begin(), b.end());
    ans = max(ans, solve(a, b));
    cout << ans;
    return 0;
}
