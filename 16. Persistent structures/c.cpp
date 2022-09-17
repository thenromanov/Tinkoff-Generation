#include <bits/stdc++.h>
using namespace std;

const int logn = 18;

struct node {
    vector <int> up;
    int x;

    node() {};

    node(int x) {
        this->x = x;
        up.resize(logn);
    }
};

vector <node> v;
vector <pair <int, int>> id;

void insert(int t, int x) {
    if (t == 0) {
        id.push_back({(int)v.size(), 0});
        v.push_back(node(x));
    } else {
        id.push_back({(int)v.size(), id[t - 1].second + 1});
        v.push_back(node(x));
        v.back().up[0] = id[t - 1].first;
        for (int l = 1; l < logn; l++) v.back().up[l] = v[v.back().up[l - 1]].up[l - 1];
    }
}

int get(int t) {
    auto [cur, c] = id[t - 1];
    for (int l = 0; l < logn; l++) {
        if ((c >> l) & 1) cur = v[cur].up[l];
    }
    id.push_back({id[t - 1].first, id[t - 1].second - 1});
    return v[cur].x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    for (int i = 0, c; i < n; i++) {
        cin >> c;
        if (c == 1) {
            int t, x; cin >> t >> x;
            insert(t, x);
        } else {
            int t; cin >> t;
            cout << get(t) << '\n';
        }
    }
    return 0;
}