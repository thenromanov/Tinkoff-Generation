#include <bits/stdc++.h>
using namespace std;

const int alpha = 26;

struct node {
    unordered_map <int, node*> childs;
    node *link = nullptr, *up = nullptr, *p;
    int pch, term = -1;

    node(node* p, int pch) {
        this->p = p;
        this->pch = pch;
    }
};

int get(char ch)  {return ch - 'a'; }

node* root = new node(0, -1);

node* get_link(node* v, int c);

node* get_sufflink(node* v) {
    if (v->link == nullptr) {
        if (v == root || v->p == root) v->link = root;
        else v->link = get_link(get_sufflink(v->p), v->pch);
    }
    return v->link;
}

node* get_link(node* v, int c) {
    if (v->childs.find(c) != v->childs.end()) return v->childs[c];
    if (v == root) return root;
    return get_link(get_sufflink(v), c);
}

node* get_up(node* v) {
    if (v->up == nullptr) {
        if (get_sufflink(v)->term != -1) v->up = get_sufflink(v);
        else if (get_sufflink(v) == root) v->up = root;
        else v->up = get_up(get_sufflink(v));
    }
    return v->up;
}

void insert(string &s, int id) {
    node* v = root;
    for (auto u : s) {
        int c = get(u);
        if (v->childs.find(c) == v->childs.end()) v->childs[c] = new node(v, c);
        v = v->childs[c];
    }
    v->term = id;
}

int main() {
    freopen("outputik.txt", "w", stdout);
    freopen("inputik.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string t; cin >> t;
    int m; cin >> m;
    vector <int> sz, qnum(m);
    map <string, int> mp;
    for (int i = 0; i < m; i++) {
        string s; cin >> s;
        if (mp.find(s) == mp.end()) {
            mp[s] = mp.size();
            sz.push_back((int)s.size());
            insert(s, mp[s]);
        }
        qnum[i] = mp[s];
    }
    vector <vector <int>> res((int)mp.size());
    node* state = root;
    for (int i = 0; i < (int)t.size(); i++) {
        int c = get(t[i]);
        state = get_link(state, c);
        node* restate = state;
        while (restate != root) {
            if (restate->term != -1) res[restate->term].push_back(i - sz[restate->term] + 1);
            restate = get_up(restate);
        }
    }
    for (int i = 0; i < m; i++) {
        cout << (int)res[qnum[i]].size() << ' ';
        for (int u : res[qnum[i]]) cout << u + 1 << ' ';
        cout << '\n';
    }
    return 0;
}