#include <bits/stdc++.h>
using namespace std;

unordered_set <int64_t> st;

int64_t hpair(int a, int b) {
    if (a > b) swap(a, b);
    return 179179LL * a + b;
}

int find(int a, int b) {
    return st.find(hpair(a, b)) != st.end();
}

void solve(int l, int r) {
    r = min(r, l + 4);
    vector <int> v;
    for (int i = l; i <= r; i++) v.push_back(i);
    if (v.size() < 3) {
        cout << "-1\n";
        return;
    }
    bool found = false;
    do {
        int c = find(v[0], v[1]);
        for (int i = 2; i < (int)v.size(); i++) {
            if (find(v[i], v[i - 1]) != c) break;
            if (find(v[i], v[0]) == c) {
                cout << i + 1 << ' ';
                for (int j = 0; j <= i; j++) cout << v[j] << ' ';
                cout << '\n';
                found = true;
                break;
            }
        }
    } while (!found && next_permutation(v.begin(), v.end()));
    if (!found) cout << "-1\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m; cin >> n >> m;
    for (int i = 0, v, u; i < m; i++) {
        cin >> v >> u;
        st.insert(hpair(v, u));
    }
    int q; cin >> q;
    while (q--) {
        int l, r; cin >> l >> r;
        solve(l, r);
    }
    return 0;
}