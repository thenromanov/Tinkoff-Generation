#include <bits/stdc++.h>
using namespace std;

const int64_t inf = 2e18 + 179;
const int maxsize = 1e9 + 179;
const int maxn = 2e5 + 179;

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
        this->lborder = 0;
        this->rborder = maxsize;
    }

    void pour(LiChao &t, node *p) {
        if (p == nullptr) return;
        if (p->l) pour(t, p->l);
        if (p->r) pour(t, p->r);
        if (p->ln.b != inf) t.add_line(p->ln);
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

int n;
vector <LiChao> t(2 * maxn);

void build() {
    for (int i = n - 1; i > 0; i--) t[i << 1].pour(t[i]), t[i << 1 | 1].pour(t[i]);
}

int64_t query(int l, int r, int64_t x) {
    int64_t res = inf;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = min(res, t[l++].get(x));
        if (r & 1) res = min(res, t[--r].get(x));
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int m; cin >> n >> m;
    vector <pair <int64_t, int64_t>> v(n);
    for (int i = 0; i < n; i++) cin >> v[i].first >> v[i].second;
    for (int i = 0; i < n; i++) t[n + i].add_line(line(-2LL * v[i].first, v[i].first * v[i].first + v[i].second));
    build();
    for (int i = 0; i < m; i++) {
        int64_t c; cin >> c;
        vector <int> d = {-1, n};
        int k; cin >> k;
        for (int j = 0, p; j < k; j++) {
            cin >> p;
            d.push_back(p - 1);
        }
        sort(d.begin(), d.end());
        int64_t ans = inf;
        for (int j = 1; j < d.size(); j++) {
            int l = d[j - 1] + 1, r = d[j] - 1;
            if (r < l) continue;
            ans = min(ans, query(l, r + 1, c));
        }
        cout << c * c + ans << '\n';
    }
    return 0;
}