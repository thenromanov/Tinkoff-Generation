#include <iostream>
#include <vector>
#include <cassert>
#include <cstdio>
using namespace std;
const int N = 100000; // 10^5
const int INF = 1000000000; // 10^9
#define TASK "lamps"
typedef pair <int, int> Segment;

const Segment ALL = make_pair(-INF, INF);
const Segment EMPTY = make_pair(1, 0);

vector<int> g[N];
vector<Segment> childSeg[N], prefInt[N], suffInt[N];
Segment segs[N], subtree[N];
bool ans[N];

Segment intersect(const Segment& a, const Segment& b) {
    int l = max(a.first, b.first);
    int r = min(a.second, b.second);
    if (l > r)
        return EMPTY;
    return make_pair(l, r);
}

Segment extend(const Segment& a, const Segment& b) {
    if (a.first > a.second)
        return EMPTY;
    if (b.first > b.second)
        return EMPTY;
    return make_pair(a.first + b.first, a.second + b.second);
}

Segment dfsCalcSubtree(int v, int p) {
    if (g[v].size() == 1 && p != -1) {
        return segs[v];
    }
    pair <int, int> subInters = ALL;
    int degree = g[v].size();
    for (int i = 0; i < degree; ++i) {
        int to = g[v][i];
        if (to != p) {
            Segment tmp = dfsCalcSubtree(to, v);
            subInters = intersect(subInters, tmp);
            childSeg[v].push_back(tmp);
        } else {
            childSeg[v].push_back(ALL);
        }
    }

    prefInt[v].resize(degree);
    suffInt[v].resize(degree);

    prefInt[v][0] = childSeg[v][0];
    suffInt[v][degree - 1] = childSeg[v][degree - 1];
    for (int i = 1; i < degree; ++i) {
        prefInt[v][i] = intersect(childSeg[v][i], prefInt[v][i - 1]);
        int j = degree - i - 1;
        suffInt[v][j] = intersect(childSeg[v][j], suffInt[v][j + 1]);
    }

    if (subInters.first <= subInters.second) {
        subtree[v] = subInters;
    } else
        subtree[v] = EMPTY;
    return extend(subtree[v], segs[v]);
}


void dfsCalc(int v, int p, const Segment& upSeg) {
    if (g[v].size() == 1 && p != -1) {
        ans[v] = upSeg.first <= upSeg.second;
        return;
    }
    Segment res = intersect(upSeg, subtree[v]);
    ans[v] = res.first <= res.second;
    int degree = g[v].size();
    for (int i = 0; i < degree; ++i) {
        int to = g[v][i];
        if (to != p) {
            Segment pref = (i > 0 ? prefInt[v][i - 1] : ALL);
            Segment suff = (i + 1 < degree ? suffInt[v][i + 1] : ALL);
            Segment newUpSeg = extend(
                                    intersect(intersect(pref, suff), upSeg),
                                    segs[v]);
            if (g[v].size() == 1) {
                newUpSeg = segs[v];
            }
            dfsCalc(to, v, newUpSeg);
        }
    }
}

int main() {
    freopen(TASK".in", "r", stdin);
    freopen(TASK".out", "w", stdout);

    int n;
    cin >> n;
    for (int i = 0; i + 1 < n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        --x;--y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &segs[i].first, &segs[i].second);
    }

    dfsCalcSubtree(0, -1);
    dfsCalc(0, -1, ALL);

    for (int v = 0; v < n; ++v)
        if (v + 1 == n)
            printf("%d\n", ans[v]);
        else
            printf("%d ", ans[v]);
    return 0;
}
