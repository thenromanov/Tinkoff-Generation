#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    vector <int> v(3 * n);
    for (int& u : v) cin >> u;
    multiset <int> l, r, buff;
    priority_queue <int> q;
    int64_t suml = 0, sumr = 0;
    for (int i = 0; i < n; i++) {
        l.insert(v[i]);
        suml += v[i];
    }
    for (int i = n; i < 3 * n; i++) q.push(v[i]);
    for (int i = 0; i < n; i++) {
        buff.insert(q.top());
        q.pop();
    }
    for (int i = 0; i < n; i++) {
        r.insert(q.top());
        sumr += q.top();
        q.pop();
    }
    int64_t ans = suml - sumr;
    for (int i = n; i < 2 * n; i++) {
        if (buff.find(v[i]) != buff.end()) buff.erase(buff.find(v[i]));
        else {
            sumr -= v[i];
            r.erase(v[i]);
            sumr += *buff.begin();
            r.insert(*buff.begin());
            buff.erase(buff.begin());
        }
        if (v[i] > *l.begin()) {
            suml -= *l.begin();
            l.erase(l.begin());
            suml += v[i];
            l.insert(v[i]);
        }
        ans = max(ans, suml - sumr);
    }
    cout << ans;
    return 0;
}