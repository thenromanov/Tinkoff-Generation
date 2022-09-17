#include <bits/stdc++.h>
using namespace std;

pair <vector <int>, vector <int>> suffarray(string& s) {
    s += '$';
    int n = (int)s.size();
    vector <int> p(n), c(n);
    vector <pair <int, int>> a(n);
    for (int i = 0; i < n; i++) a[i] = {s[i], i};
    sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) p[i] = a[i].second;
    c[p[0]] = 0;
    for (int i = 1; i < n; i++) c[p[i]] = c[p[i - 1]] + (a[i].first != a[i - 1].first);
    int k = 0;
    while ((1 << k) < n) {
        for (int i = 0; i < n; i++) p[i] = (p[i] - (1 << k) + n) % n;
        vector <int> cnt(n);
        for (auto x : c) cnt[x]++;
        vector <int> p_new(n), c_new(n), pos(n);
        for (int i = 1; i < n; i++) pos[i] = pos[i - 1] + cnt[i - 1];
        for (auto x : p) {
            p_new[pos[c[x]]] = x;
            pos[c[x]]++;
        }
        p = p_new;
        c_new[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            pair <int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]}, now = {c[p[i]], c[(p[i] + (1 << k)) % n]};
            c_new[p[i]] = c_new[p[i - 1]] + (prev != now);
        }
        c = c_new;
        k++;
    }
    s.pop_back();
    p.erase(p.begin());
    c.pop_back();
    for (auto& u : c) u--;
    return {p, c};
}

vector <int> lcp(string& s, vector <int>& p, vector <int>& c) {
    int n = (int)s.size(), l = 0;
    vector <int> lcp(n);
    for (int i = 0; i < n; i++) {
        if (c[i] == n - 1) continue;
        int nxt = p[c[i] + 1];
        while (max(i, nxt) + l < n && s[i + l] == s[nxt + l]) l++;
        lcp[c[i] + 1] = l;
        l = max(0, l - 1);
    }
    return lcp;
}

bool check(vector <int>& mcp, int m) {
    int n = (int)mcp.size();
    set <int> able;
    able.insert(n);
    for (int i = n - 1; i >= 0; i--) {
        auto it = able.lower_bound(i + m);
        if (it != able.end() && *it <= i + mcp[i]) able.insert(i);
    }
    return able.find(0) != able.end();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string s, t; cin >> s >> t;
    int n = (int)s.size(), m = (int)t.size();
    string q = s + t;
    auto [p, c] = suffarray(q);
    vector <int> prf = lcp(q, p, c), mcp(n);
    int lastpos = -1, curmin = INT_MAX;
    for (int i = 1; i < n + m; i++) {
        curmin = min(curmin, prf[i]);
        if (p[i] < n) mcp[p[i]] = curmin;
        else curmin = INT_MAX;
    }
    curmin = 0;
    for (int i = n + m - 1; i >= 0; i--) {
        if (p[i] < n) mcp[p[i]] = max(mcp[p[i]], curmin);
        else curmin = INT_MAX;
        curmin = min(curmin, prf[i]);
    }
    int l = 0, r = n + 1;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        if (check(mcp, m)) l = m;
        else r = m;
    }
    cout << (l == 0 ? 1 : l) << '\n';
    return 0;
}