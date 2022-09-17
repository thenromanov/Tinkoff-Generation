#include <bits/stdc++.h>
using namespace std;

const int alpha = 26;
const int maxn = 1e6 + 7;
const int logn = 20;

int COUNTER = 1;

struct node {
    int id;
    vector <node*> ch;

    node() {};
    node(int id) : id(id) {ch.resize(26);};
};

struct ft {
    int n;
    vector <int64_t> t;

    ft(int n) {
        this->n = n;
        t.resize(n + 1);
    }

    void inc(int k, int x) {
        for (; k <= n; k += k & -k) t[k] += x;
    }

    int64_t sum(int r) {
        int64_t ans = 0;
        for (; r > 0; r -= r & -r) ans += t[r];
        return ans;
    }

    int64_t sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};

node* root = new node(0);

int insert(const string& s) {
    node* v = root;
    for (int i = 0; i < (int)s.size(); i++) {
        int c = s[i] - 'a';
        if (!v->ch[c]) v->ch[c] = new node(COUNTER++);
        v = v->ch[c];
    }
    return v->id;
}

vector <int> idpos(maxn), sz(maxn, 1), order;
vector <vector <int>> up(logn, vector <int> (maxn));

void dfs(node* v, int p = -1) {
    idpos[v->id] = order.size();
    up[0][idpos[v->id]] = (p == -1 ? 0 : p);
    for (int l = 1; l < logn; l++) up[l][idpos[v->id]] = up[l - 1][up[l - 1][idpos[v->id]]];
    order.push_back(v->id);
    for (int i = 0; i < alpha; i++) {
        if (v->ch[i]) {
            dfs(v->ch[i], idpos[v->id]);
            sz[idpos[v->id]] += sz[idpos[v->ch[i]->id]];
        }
    }
}

int par(int v, int k) {
    for (int l = logn - 1; l >= 0; l--) {
        if (k - (1 << l) >= 0) {
            k -= (1 << l);
            v = up[l][v];
        }
    }
    return v;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m; cin >> n >> m;
    vector <pair <string, int>> v(n);
    vector <int> id(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i].first >> v[i].second;
        id[i] = insert(v[i].first);
    }
    dfs(root);
    ft tree(order.size() + 1);
    for (int i = 0; i < n; i++) {
        tree.inc(idpos[id[i]] + 1, v[i].second);
        tree.inc(idpos[id[i]] + sz[idpos[id[i]]] + 1, -v[i].second);
    }
    for (int i = 0; i < m; i++) {
        char c; cin >> c;
        int u, k; cin >> u >> k; u--;
        if (c == '?') {
            if (k > (int)v[u].first.size()) {
                cout << 0 << '\n';
                continue;
            }
            k = (int)v[u].first.size() - k;
            int p = par(idpos[id[u]], k + 1);
            cout << tree.sum(0, idpos[id[u]] + 1) - tree.sum(0, p + 1) << '\n';
        } else {
            tree.inc(idpos[id[u]] + 1, k);
            tree.inc(idpos[id[u]] + sz[idpos[id[u]]] + 1, -k);
        }
    }
    return 0;
}