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

struct LiChao {
    struct node {
        node *l = nullptr, *r = nullptr;
        line ln;
        
        node() : ln(line(0LL, inf)) {};
        node(line _ln) : ln(_ln) {};
    };
    node *root;
    int lborder, rborder;

    LiChao() {
        root = new node();
        this->lborder = -maxn;
        this->rborder = maxn;
    }

    void pour(LiChao &t, node *p) {
        if (p == nullptr) return;
        if (p->l) pour(t, p->l);
        if (p->r) pour(t, p->r);
        if (p->ln.b != inf) t.add_line(p->ln);
        p = nullptr;
    }

    void pour(LiChao &t) {
        pour(t, root);
    }

    void add_line(node *&p, int lb, int rb, line& nline) {
        if (p == nullptr) {
            p = new node(nline);
            return;
        }
        int64_t trl = p->ln.get(lb), trr = p->ln.get(rb);
        int64_t vl = nline.get(lb), vr = nline.get(rb);
        if (trl <= vl && trr <= vr) return;
        if (trl > vl && trr > vr) {
            p->ln = nline; 
            return;
        }
        int mid = (lb + rb) / 2;
        if (trl > vl) swap(p->ln, nline);
        if (p->ln.get(mid) < nline.get(mid)) add_line(p->r, mid + 1, rb, nline);
        else swap(p->ln, nline), add_line(p->l, lb, mid, nline);
    }

    void add_line(line nline) {
        add_line(root, lborder, rborder, nline);
    }

    int64_t get(node *&p, int lb, int rb, int64_t x) {
        if (!p) return inf;
        if (lb == rb) return p->ln.get(x);
        int mid = (lb + rb) / 2;
        if (mid >= x) return min(p->ln.get(x), get(p->l, lb, mid, x));
        return min(p->ln.get(x), get(p->r, mid + 1, rb, x));
    }

    int64_t get(int64_t x) {
        return get(root, lborder, rborder, x);
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
    curr.add_line(line(c[v].second, ans[v]));
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