// ∫

#include <bits/stdc++.h>
using namespace std;

const int alpha = 26;
const int maxn = 3e5 + 179;

struct node {
    vector <node*> childs;
    int size, cst;
    bool root;

    node(bool rt = false, int sz = 1) {
        childs.resize(alpha);
        size = sz;
        root = rt;
    }
};

int get(char c) { return c - 'a'; }

void unite(node *v, node *u) {
    v->size = !v->root;
    for (int c = 0; c < alpha; c++) {
        if (v->childs[c] && u->childs[c]) unite(v->childs[c], u->childs[c]);
        else if (v->childs[c] == nullptr && u->childs[c]) swap(v->childs[c], u->childs[c]);
        if (v->childs[c]) v->size += v->childs[c]->size;
    }
    u = nullptr;
}

vector <vector <int>> g(maxn);
vector <node*> stree(maxn, nullptr);
vector <int> c(maxn), symb(maxn);

void dfs(int v, int p = -1) {
    int rpos = -1, sz = 0;
    for (int u : g[v]) {
        if (u != p) {
            dfs(u, v);
            if (stree[u] && stree[u]->size > sz) {
                rpos = u;
                sz = stree[u]->size;
            }
        }
    }
    if (rpos == -1) {
        stree[v] = new node(true, 1);
        stree[v]->childs[symb[v]] = new node();
    } else {
        for (int u : g[v]) {
            if (u != p && u != rpos) {
                unite(stree[rpos], stree[u]);
            }
        }
        stree[rpos]->size++;
        stree[v] = new node(true, stree[rpos]->size);
        stree[v]->childs[symb[v]] = stree[rpos];
        stree[rpos]->root = false;
    }
    c[v] += stree[v]->size;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    for (int i = 0; i < n; i++) cin >> c[i];
    for (int i = 0; i < n; i++) {
        char ch; cin >> ch;
        symb[i] = get(ch);
    }
    for (int i = 0, v, u; i < n - 1; i++) {
        cin >> v >> u; v--, u--;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    dfs(0);
    int res = *max_element(c.begin(), c.end()), cnt = 0;
    cout << res << '\n';
    for (int i = 0; i < n; i++) cnt += c[i] == res;
    cout << cnt << '\n';
    return 0;
}