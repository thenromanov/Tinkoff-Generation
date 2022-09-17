#include <bits/stdc++.h>
using namespace std;

pair <vector <int>, vector <int>> suffarray(string& s) {
    s += "$";
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string s; cin >> s;
    int n = (int)s.size();
    auto [p, c] = suffarray(s);
    vector <int> lpref = lcp(s, p, c);
    int64_t cur = 0, k; cin >> k; k--;
    int i = 0;
    for (; i < n; i++) {
        if (k < cur + n - p[i] - lpref[i]) {
            for (int j = p[i]; j <= p[i] + k - cur + lpref[i]; j++) cout << s[j];
            break;
        }
        cur += n - p[i] - lpref[i];
    }
    if (i == n) {
        for (int j = p[n - 1]; j < n; j++) cout << s[j];
    }
    return 0;
}