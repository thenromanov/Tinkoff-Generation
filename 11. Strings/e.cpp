#include <bits/stdc++.h>
using namespace std;

pair <vector <int>, vector <int>> suffarray(vector <int>& s) {
    s.push_back(0);
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

vector <int> lcp(vector <int>& s, vector <int>& p, vector <int>& c) {
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m; cin >> n >> m;
    vector <int> v(n);
    for (int& u : v) cin >> u;
    auto [p, c] = suffarray(v);
    vector <int> l = lcp(v, p, c);
    int64_t w = 1, h = n, b = 0;
    stack <pair <int, int64_t>> st;
    for (int i = 0; i < n; i++) {
        int64_t x = 1;
        while (!st.empty() && l[i] <= l[st.top().first]) {
            x += st.top().second;
            int id = st.top().first;
            st.pop();
            if (x * l[id] > w * h) w = x, h = l[id], b = p[id];
        }
        st.push({i, x});
    }
    cout << w * h << '\n' << h << '\n';
    for (int i = b; i < b + h; i++) cout << v[i] << ' ';
    return 0;
}