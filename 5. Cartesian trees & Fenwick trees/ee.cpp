#include <bits/stdc++.h>
using namespace std;

struct ft {
    int n;
    vector <int> t;

    ft(int n) {
        this->n = n;
        t.resize(n + 1);
    }

    void inc(int k, int x) {
        for (; k <= n; k += k & -k) t[k] += x;
    }

    int sum(int r) {
        int ans = 0;
        for (; r > 0; r -= r & -r) ans += t[r];
        return ans;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m; cin >> n >> m;
    vector <int> order, used(n), v(m);
    queue <int> q;
    for (int& u : v) cin >> u, u--;
    for (int i = 0, val; i < n; i++) {
        cin >> val; val--;
        q.push(val);
    }
    for (int u : v) {
        if (!used[u]) {
            while (!q.empty()) {
                int x = q.front();
                q.pop();
                order.push_back(x);
                used[x] = 1;
                if (x == u) break;
            }
        } else {
            order.push_back(u);
        }
    }
    vector <int> ans(order.size()), last(n, order.size());
    vector <pair <int, int>> req;
    for (int i = order.size() - 1; i >= 0; i--) {
        req.push_back({i, last[order[i]]});
        last[order[i]] = i;
    }
    sort(req.begin(), req.end(), [&](const pair <int, int>& a, const pair <int, int>& b) {return a.second == b.second ? a.first < b.first : a.second < b.second;});
    last.assign(n, -1);
    int pos = 0;
    ft tree(order.size() + 1);
    for (int i = 0; i <= order.size(); i++) {
        if (i < order.size() && last[order[i]] != -1) tree.inc(last[order[i]] + 1, -1);
        tree.inc(i + 1, 1);
        if (i < order.size()) last[order[i]] = i;
        while (pos < req.size() && req[pos].second == i) {
            ans[req[pos].first] = tree.sum(req[pos].first + 2, req[pos].second) + 1;
            pos++;
        }
    }
    cout << ans.size() << '\n';
    for (auto u : ans) cout << u << ' ';
    return 0;
}