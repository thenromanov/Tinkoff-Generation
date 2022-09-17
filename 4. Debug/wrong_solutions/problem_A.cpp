#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;
#define y1 _y1

const int MAXN = 1e5;
int x1[MAXN], y1[MAXN], x2[MAXN], y2[MAXN];

vector <int> Xes, Yes;

pair <int, int> tree[MAXN * 4];
int mod[MAXN * 4];

inline pair <int, int> get_val(int v) {
	return {tree[v].first + mod[v], tree[v].second};
}

inline pair <int, int> merge(pair <int, int> A, pair <int, int> B) {
	if (A.first < B.first) return A;
	if (A.first > B.first) return B;
	return {A.first, A.second + B.second};
}

inline void push(int v) {
	mod[v * 2] += mod[v];
	mod[v * 2 + 1] += mod[v];
}

inline void build (int v, int l, int r) {
	if (l == r) {
		tree[v] = {0, Yes[l + 1] - Yes[l]};
	} else {
		int m = (l + r) / 2;
		build(v * 2, l, m);
		build(v * 2 + 1, m + 1, r);
		tree[v] = merge(get_val(v * 2), get_val(v * 2 + 1));
	}
}

inline void update (int v, int cl, int cr, int l, int r, int val) {
	if (cr < l || r < cl) return;
	if (l <= cl && cr <= r) {
		mod[v] += val;
		return;
	}
	push(v);
	int cm = (cl + cr) / 2;
	update(v * 2, cl, cm, l, r, val);
	update(v * 2 + 1, cm + 1, cr, l, r, val);
	tree[v] = merge(get_val(v * 2), get_val(v * 2 + 1));
}

signed main() {
	ios_base::sync_with_stdio(false);
	int n;
	cin >> n;
	if (n == 0) {
		cout << 0 << endl;
		return 0;
	}
	for (int i = 0; i < n; i++) {
		cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
		Xes.push_back(x1[i]);
		Xes.push_back(x2[i]);

		Yes.push_back(y1[i]);
		Yes.push_back(y2[i]);
	}
	sort(Xes.begin(), Xes.end());
	Xes.resize(unique(Xes.begin(), Xes.end()) - Xes.begin());
	sort(Yes.begin(), Yes.end());
	Yes.resize(unique(Yes.begin(), Yes.end()) - Yes.begin());

	int m = Yes.size() - 1;
	build(1, 0, m - 1);
	int k = Xes.size();
	vector <vector <pair <pair <int, int>, int> > > events(k);
	for (int i = 0; i < n; i++) {
		int down = lower_bound(Yes.begin(), Yes.end(), y1[i]) - Yes.begin();
		int up = upper_bound(Yes.begin(), Yes.end(), y2[i]) - Yes.begin();
		events[lower_bound(Xes.begin(), Xes.end(), x1[i]) - Xes.begin()].push_back({{down, up - 1},  1});
		events[upper_bound(Xes.begin(), Xes.end(), x2[i]) - Xes.begin()].push_back({{down, up - 1}, -1});
	}
	long long ans = 0, leng = Yes.back() - Yes[0];
	for (int i = 0; i + 1 < k; i++) {
		for (auto e : events[i])
			update(1, 0, m - 1, e.first.first, e.first.second, e.second);
		pair <int, int> e = get_val(1);
		long long num = leng;
		if (e.first == 0)
			num -= e.second;
		ans += num * (Xes[i + 1] - Xes[i]);
	}
	cout << ans << endl;
	return 0;
}