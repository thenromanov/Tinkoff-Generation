#include <bits/stdc++.h>
using namespace std;

const int alpha = 26;

struct node {
    vector <node*> childs, links, revlinks;
    node *link = nullptr, *p;
    int pch, depth;
    vector <pair <int, pair <int, int>>> queries;
    set <int> terms;

    node(node *p, int pch, int depth) {
        this->p = p;
        this->pch = pch;
        this->depth = depth;
        childs.resize(alpha, nullptr);
        links.resize(alpha, nullptr);
    }
};

int get(char c) { return c - 'a'; }

node *root = new node(nullptr, -1, 0);

node* get_link(node *v, int c);

node* get_sufflink(node *v) {
    if (v->link == nullptr) {
        if (v == root || v->p == root) v->link = root;
        else v->link = get_link(get_sufflink(v->p), v->pch);
    }
    return v->link;
}

node* get_link(node *v, int c) {
    if (v->links[c] == nullptr) {
        if (v->childs[c]) v->links[c] = v->childs[c];
        else if (v == root) v->links[c] = root;
        else v->links[c] = get_link(get_sufflink(v), c);
    }
    return v->links[c];
}

void insert(string &s, pair <int, pair <int, int>> q) {
    node *v = root;
    int i = 1;
    for (char u : s) {
        int c = get(u);
        if (v->childs[c] == nullptr) v->childs[c] = new node(v, c, i);
        v = v->childs[c];
        i++;
    }
    v->queries.push_back(q);
}

vector <node*> nodes;

void dfs(node* v) {
    nodes.push_back(v);
    for (int c = 0; c < alpha; c++) {
        if (v->childs[c] == nullptr) continue;
        dfs(v->childs[c]);
    }
}

void get_ans(vector <int>& ans) {
    dfs(root);
    sort(nodes.begin(), nodes.end(), [](const node *a, const node *b) {return a->depth > b->depth;});
    for (auto v : nodes) {
        int msize = (int)v->terms.size(), mchar = -1;
        for (int i = 0; i < (int)v->revlinks.size(); i++) {
            if ((int)v->revlinks[i]->terms.size() > msize) {
                msize = (int)v->revlinks[i]->terms.size();
                mchar = i;
            }
        }
        if (mchar != -1) swap(v->terms, v->revlinks[mchar]->terms);
        for (auto from : v->revlinks) {
            for (int u : from->terms) v->terms.insert(u);
            from->terms.clear();
        }
        for (auto [i, q] : v->queries) {
            auto it = v->terms.lower_bound(q.first);
            if (it == v->terms.end()) continue;
            ans[i] = *it <= q.second;
        }
        get_sufflink(v)->revlinks.push_back(v);
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string t; cin >> t;
    int n; cin >> n;
    vector <int> ans(n);
    for (int i = 0, l, r; i < n; i++) {
        string s; cin >> l >> r >> s; l--, r--;
        if (r - l + 1 < (int)s.size()) continue;
        insert(s, {i, {l + (int)s.size() - 1, r}});
    }
    node *state = root;
    for (int i = 0; i < (int)t.size(); i++) {
        int c = get(t[i]);
        state = get_link(state, c);
        state->terms.insert(i);
    }
    get_ans(ans);
    for (int u : ans) cout << (u ? '+' : '-');
    return 0;
}