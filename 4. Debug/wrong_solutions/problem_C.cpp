#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <ctime>
#include <bitset>
#include <complex>
using namespace std;

typedef long long ll;

#define int ll

int n, k;

inline void init() {

}

void sleep(double t) {
	clock_t s = clock();
	while ((clock() - s) / 1000000.0 < t);
}

inline void solve() {
	init();
	if (n == 1 && k == 1) {
		cout << 0 << '\n';
		return;
	}
	int lft = n - 1;
	k--;
	if (k == 0 || lft % k != 0) {
		cout << "-1\n";
		return;
	}
	int cnt = lft / k;
	cout << cnt << '\n';
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> k)
		solve();
	return 0;
}