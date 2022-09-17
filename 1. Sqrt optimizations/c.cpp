#include <bits/stdc++.h>
using namespace std;

const int alpha = 26;

struct node {
    vector <node*> childs, links;
    node *link = 0, *up = 0, *p;
    int pch;
    bool term = false;
    vector <int> terms;

    node(node* p, int pch) {
        this->p = p;
        this->pch = pch;
        childs.resize(alpha, 0);
        links.resize(alpha, 0);
    }
};

int get(char ch) {
    return ch - 'a';
}

node* root = new node(0, -1);

node* get_link(node* v, int c);

node* get_sufflink(node* v) {
    if (!v->link) {
        if (v == root || v->p == root) v->link = root;
        else v->link = get_link(get_sufflink(v->p), v->pch);
    }
    return v->link;
}

node* get_link(node* v, int c) {
    if (!v->links[c]) {
        if (v->childs[c]) v->links[c] = v->childs[c];
        else if (v == root) v->links[c] = root;
        else v->links[c] = get_link(get_sufflink(v), c);
    }
    return v->links[c];
}

node* get_up(node* v) {
    if (!v->up) {
        if (get_sufflink(v)->term) v->up = get_sufflink(v);
        else if (get_sufflink(v) == root) v->up = root;
        else v->up = get_up(get_sufflink(v));
    }
    return v->up;
}

void insert(string &s, int id) {
    node* v = root;
    for (auto u : s) {
        int c = get(u);
        if (!v->childs[c]) v->childs[c] = new node(v, c);
        v = v->childs[c];
    }
    v->term = true;
    v->terms.push_back(id);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string t; cin >> t;
    int m; cin >> m;
    vector <int> sz(m), need(m);
    for (int i = 0; i < m; i++) {
        string s; cin >> need[i] >> s;
        sz[i] = (int)s.size();
        insert(s, i);
    }
    vector <vector <int>> res(m);
    node* state = root;
    for (int i = 0; i < (int)t.size(); i++) {
        int c = get(t[i]);
        state = get_link(state, c);
        node* restate = state;
        while (restate != root) {
            for (int id : restate->terms) res[id].push_back(i - sz[id] + 1);
            restate = get_up(restate);
        }
    }
    for (int i = 0; i < m; i++) {
        if ((int)res[i].size() < need[i]) {
            cout << -1 << '\n';
            continue;
        }
        int ans = INT_MAX;
        for (int j = need[i] - 1; j < (int)res[i].size(); j++) ans = min(ans, res[i][j] - res[i][j - need[i] + 1]);
        cout << ans + sz[i] << '\n';
    }
    return 0;
}

