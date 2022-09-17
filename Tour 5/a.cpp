#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, k; cin >> n >> m >> k;
    set <int> st;
    vector <queue <int>> mp(k);
    vector <int> v(n), deleted(n);
    vector <vector <int>> ans;
    for (int i = 0; i < n; i++) cin >> v[i], v[i]--;
    for (int i = 0; i < n; i++) {
        if (i - m - 1 >= 0 && !deleted[i - m - 1]) {
            if (mp[v[i - m - 1]].size() == 1) st.erase(v[i - m - 1]);
            mp[v[i - m - 1]].pop();
            deleted[i - m - 1] = 1;
        }
        st.insert(v[i]);
        mp[v[i]].push(i);
        while (st.size() == k) {
            vector <int> res(k);
            for (int j = 0; j < k; j++) {
                if (mp[j].size() == 1) st.erase(j);
                res[j] = mp[j].front();
                deleted[mp[j].front()] = 1;
                mp[j].pop();
            }
            ans.push_back(res);
        }
    }
    cout << ans.size() << '\n';
    for (auto u : ans) {
        for (int i : u) cout << i + 1 << ' ';
        cout << '\n';
    }
    return 0;
}