#include <bits/stdc++.h>
using namespace std;

mt19937 gena(chrono::steady_clock::now().time_since_epoch().count());

struct node {
    int p;
    int64_t k, val, max;
    node *l = nullptr, *r = nullptr;
    node(int64_t _k, int v) : p(gena()), k(_k), max(v), val(v) {};
};

int64_t upd_max(node* v) { return v ? v->max : LLONG_MIN; }
void upd(node* v) { v->max = max({upd_max(v->l), upd_max(v->r), v->val}); }

node* merge(node *l, node *r) {
    if (!l) return r;
    if (!r) return l;
    if (l->p > r->p) {
        l->r = merge(l->r, r);
        upd(l);
        return l;
    } else {
        r->l = merge(l, r->l);
        upd(r);
        return r;
    }
}

pair <node*, node*> split(node *p, int64_t k) {
    if (!p) return {nullptr, nullptr};
    if (p->k <= k) {
        auto [l, r] = split(p->r, k);
        p->r = l;
        upd(p);
        return {p, r};
    } else {
        auto [l, r] = split(p->l, k);
        p->l = r;
        upd(p);
        return {l, p};
    }
}

void insert(node *&p, int64_t k, int v) {
    auto [l, r] = split(p, k);
    node *t = new node(k, v);
    p = merge(l, merge(t, r));
}

int get_max(node *&p, int64_t lq, int64_t rq) {
    auto [t, r] = split(p, rq);
    auto [l, m] = split(t, lq);
    int res = upd_max(m);
    p = merge(l, merge(m, r));
    return res;
}

vector <vector <pair <int, int64_t>>> g, dist;
vector <int> used, sz;
vector <node*> dp;

int get_size(int v, int p = -1) {
    if (used[v]) return 0;
    sz[v] = 1;
    for (auto [u, l] : g[v]) {
        if (u != p) sz[v] += get_size(u, v);
    }
    return sz[v];
}

int get_centroid(int v, int p, int n) {
    for (auto [u, l] : g[v]) {
        if (u != p && !used[u] && sz[u] > n / 2) return get_centroid(u, v, n);
    }
    return v;
}

void get_dist(int v, int p, int c, int64_t h = 0) {
    if (used[v]) return;
    dist[v].push_back({c, h});
    for (auto [u, l] : g[v]) {
        if (u != p) get_dist(u, v, c, h + l);
    }
}

void decompose(int v) {
    get_size(v);
    int c = get_centroid(v, -1, sz[v]);
    get_dist(c, -1, c);
    used[c] = 1;
    for (auto [u, l] : g[c]) {
        if (!used[u]) decompose(u);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    g.resize(n), dist.resize(n), used.resize(n), sz.resize(n), dp.resize(n);
    for (int i = 0; i < n; i++) dp[i] = new node(0, 0);
    for (int i = 0, v, u, l; i < n - 1; i++) {
        cin >> v >> u >> l; v--, u--;
        g[v].push_back({u, l});
        g[u].push_back({v, l});
    }
    decompose(0);
    int q; cin >> q;
    vector <pair <int, int>> days(q);
    for (auto& u : days) cin >> u.second >> u.first;
    sort(days.begin(), days.end());
    int ans = 0;
    for (int i = 0; i < q; i++) {
        int t = days[i].first, v = days[i].second, maxval = 0; v--;
        for (auto [u, l] : dist[v]) {
            if (t - l < 0) continue;
            int cur = get_max(dp[u], -1, t - l) + 1;
            maxval = max(maxval, cur);
        }
        for (auto [u, l] : dist[v]) {
            insert(dp[u], t + l, maxval);
        }
        ans = max(ans, maxval);
    }
    cout << ans << '\n';
    return 0;
}