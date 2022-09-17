#include <bits/stdc++.h>
using namespace std;

const int logn = 20;
const int maxn = 5e5 + 7;

pair <vector <int>, vector <int>> suffarray(string& s) {
    s += "$";
    int n = (int)s.size();
    vector <int> p(n), c(n);
    vector <pair <char, int>> a(n);
    for (int i = 0; i < n; i++) a[i] = {s[i], i};
    sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) p[i] = a[i].second;
    c[p[0]] = 0;
    for (int i = 1; i < n; i++) c[p[i]] = c[p[i - 1]] + (a[i - 1].first != a[i].first);
    int k = 0;
    while ((1 << k) < n) {
        for (int i = 0; i < n; i++) p[i] = (p[i] - (1 << k) + n) % n;
        vector <int> cnt(n);
        for (int x : c) cnt[x]++;
        vector <int> p_new(n), c_new(n), pos(n);
        for (int i = 1; i < n; i++) pos[i] = pos[i - 1] + cnt[i - 1];
        for (int x : p) {
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
    for (int& u : c) u--;
    return {p, c};
}

vector <int> lcp(string& s, vector <int>& p, vector <int>& c) {
    int n = (int)s.size(), l = 0;
    vector <int> res(n);
    for (int i = 0; i < n; i++) {
        if (c[i] == n - 1) continue;
        int nxt = p[c[i] + 1];
        while (max(nxt, i) + l < n && s[nxt + l] == s[i + l]) l++;
        res[c[i]] = l;
        l = max(0, l - 1);
    }
    return res;
}

vector <int> mn(logn, vector <int> (maxn));

int rmq(int l, int r) {
    int t = __lg(r - l);
    return min(mn[t][l], mn[t][r - (1 << t)]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string s; cin >> s;
    int n = (int)s.size();
    auto [p, c] = suffarray(s);
    vector <int> l = lcp(s, p, c);
    for (int i = 0; i < n; i++) mn[0][i] = l[i];
    for (int l = 0; l < logn - 1; l++) {
        for (int i = 0; i + (1 << (l + 1)) < n; i++) {
            mn[l + 1][i] = min(mn[l][i], mn[l][i + (1 << l)]);
        }
    }
    int64_t ans = 0;
    for (int i = 1; i < n; i++) {
        int64_t s = 
    }
    return 0;
}