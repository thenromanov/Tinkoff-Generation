#include "bits/stdc++.h"
using namespace std;

struct node {
    node *p = nullptr;
    int64_t w = 0;

    node() {};
    node(node* p, int64_t w) : p(p), w(w) {};
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    vector <node*> history = {new node(nullptr, 0)};
    int n; cin >> n;
    int64_t ans = 0;
    for (int i = 0, t, m; i < n; i++) {
        cin >> t >> m;
        if (m == 0) history.push_back(history[t]->p);
        else history.push_back(new node(history[t], history[t]->w + m));
        ans += history.back()->w;
    }
    cout << ans << '\n';
    return 0;
}