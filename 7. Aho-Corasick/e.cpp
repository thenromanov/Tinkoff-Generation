#include <bits/stdc++.h>
using namespace std;

struct node {
    map <int, node*> childs, links;
    node *link = nullptr, *p;
    int pch, used = 0;
    bool term = false, checked = false;

    node(node *p, int pch) {
        this->p = p;
        this->pch = pch;
    }
};

int get(char c) { return c - '0'; }

node *root = new node(nullptr, -1);

node* get_link(node *v, int c);

node* get_sufflink(node *v) {
    if (v->link == nullptr) {
        if (v == root || v->p == root) v->link = root;
        else v->link = get_link(get_sufflink(v->p), v->pch);
    }
    return v->link;
}

node* get_link(node *v, int c) {
    if (v->links.find(c) == v->links.end()) {
        if (v->childs.find(c) != v->childs.end()) v->links[c] = v->childs[c];
        else if (v == root) v->links[c] = root;
        else v->links[c] = get_link(get_sufflink(v), c);
    }
    return v->links[c];
}

bool check_term(node *v) {
    if (v == root) {
        v->checked = true;
        return false;
    }
    if (v->checked == false) v->term |= check_term(get_sufflink(v)), v->checked = true;
    return v->term;
}

void add(string &s) {
    node *v = root;
    for (char u : s) {
        int c = get(u);
        if (v->childs.find(c) == v->childs.end()) v->childs[c] = new node(v, c);
        v = v->childs[c];
    }
    v->term = true;
}

bool dfs(node *v) {
    if (v->used == 1) return true;
    if (v->used == 2 || check_term(v)) return false;
    v->used = 1;
    bool res = dfs(get_link(v, 0)) || dfs(get_link(v, 1));
    v->used = 2;
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        add(s);
    }
    cout << (dfs(root) ? "TAK\n" : "NIE\n");
    return 0;
}