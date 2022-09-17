#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 7;
const int64_t k = 107;
const int64_t mod = 1e9 + 9;

int64_t getc(char c) {
    return c - ' ' + 1;
}

pair <vector <int>, vector <int>> suffarray(vector <int>& v) {
    int n = (int)v.size();
    vector <int> p(n), c(n);
    vector <pair <int, int>> a(n);
    for (int i = 0; i < n; i++) a[i] = {v[i], i};
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
    return {p, c};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string s; getline(cin, s);
    int n = (int)s.size();
    vector <int> v(n), ind;
    for (int i = 0; i < n; i++) v[i] = getc(s[i]);
    auto [p, c] = suffarray(v);
    vector <int> used(n);
    for (int i = 0; i < n; i++) {
        if (!used[c[p[i]]]) {
            ind.push_back(p[i]);
            used[c[p[i]]] = 1;
        }
    }
    int k; cin >> k; k--;
    if ((int)ind.size() <= k) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    for (int i = ind[k]; i < n; i++) cout << s[i];
    for (int i = 0; i < ind[k]; i++) cout << s[i];
    cout << '\n';
    return 0;
}