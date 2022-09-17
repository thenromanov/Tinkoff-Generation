#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 179;
const int64_t inf = 1e14 + 179;

struct line {
    int64_t k, b;

    line() {};

    line(int64_t k, int64_t b) {
        this->k = k;
        this->b = b;
    }

    int64_t get(int64_t x) {
        return k * x + b;
    }
};

struct node {
    node *l = nullptr, *r = nullptr;
    line ln;
    
    node() : ln(line(0, inf)) {};
};

struct LiChao {
    node *root;

    LiChao() {
        root = new node();
    }

    void pour(LiChao &t, node *&p) {
        if (p == nullptr) return;
        if (p->l) pour(t, p->l);
        if (p->r) pour(t, p->r);
        if (p->ln.b != inf) t.upd(p->ln);
        p = nullptr;
    }

    void pour(LiChao &t) {
        pour(t, root);
    }

    void extend(node *&p) {
        if (p->l == nullptr) p->l = new node();
        if (p->r == nullptr) p->r = new node();
    }

    void upd(node *&p, int lb, int rb, line nline) {
        if (lb > rb) return;
        int m = (lb + rb) / 2;
        bool l = nline.get(lb) < p->ln.get(lb);
        bool mid = nline.get(m) < p->ln.get(m);
        if (mid) swap(nline, p->ln);
        extend(p);
        if (l != mid) upd(p->l, lb, m - 1, nline);
        else upd(p->r, m + 1, rb, nline);
    }

    void upd(line nline) {
        upd(root, -maxn, maxn, nline);
    }

    int64_t get(node *&p, int lb, int rb, int64_t x) {
        if (lb > rb || p == nullptr) return inf;
        if (lb + 1 == rb) return p->ln.get(x);
        int m = (lb + rb) / 2;
        if (x < m) return min(p->ln.get(x), get(p->l, lb, m - 1, x));
        else return min(p->ln.get(x), get(p->r, m + 1, rb, x));
    }

    int64_t get(int64_t x) {
        return get(root, -maxn, maxn, x);
    }
};

vector <vector <int>> g(maxn);
vector <pair <int64_t, int64_t>> c(maxn);
vector <int64_t> sizes(maxn), ans(maxn);

void get_sizes(int v, int p = -1) {
    sizes[v] = 1;
    for (int u : g[v]) {
        if (u != p) {
            get_sizes(u, v);
            sizes[v] += sizes[u];
        }
    }
}

void dfs(int v, int p, LiChao& curr) {
    int mx = -1, mxn = -1;
    for (int u : g[v]) if (u != p && mx < sizes[u]) mxn = u, mx = sizes[u]; 
    if (mxn != -1) dfs(mxn, v, curr);
    for (int u : g[v]) {
        if (u != p && u != mxn) {
            LiChao temp;
            dfs(u, v, temp);
            temp.pour(curr);
        }
    }
    if (mxn != -1) ans[v] = curr.get(c[v].first);
    curr.upd(line(c[v].second, ans[v]));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    for (int i = 0; i < n; i++) cin >> c[i].first;
    for (int i = 0; i < n; i++) cin >> c[i].second;
    for (int i = 0, v, u; i < n - 1; i++) {
        cin >> v >> u; v--, u--;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    get_sizes(0);
    LiChao curr;
    dfs(0, -1, curr);
    for (int i = 0; i < n; i++) cout << ans[i] << ' ';
    return 0;
}