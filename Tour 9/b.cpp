#include <bits/stdc++.h>
using namespace std;

const int maxsum = 50 * 2007;
const int64_t inf = 1e18 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    vector <pair <int, pair <int, int>>> obj;
    int n; cin >> n;
    for (int i = 0, c, f, v; i < n; i++) {
        cin >> c >> f >> v;
        obj.push_back({f, {c, -v}});
    }
    int m; cin >> m;
    for (int i = 0, c, f, v; i < m; i++) {
        cin >> c >> f >> v;
        obj.push_back({f, {-c, v}});
    }
    sort(obj.rbegin(), obj.rend());
    vector <int64_t> dp1(maxsum, -inf);
    dp1[0] = 0;
    for (int i = 1; i <= n + m; i++) {
        vector <int64_t> dp2(maxsum, -inf);
        for (int sum = 0; sum < maxsum; sum++) {
            dp2[sum] = dp1[sum];
            if (sum - obj[i - 1].second.first >= 0 && sum - obj[i - 1].second.first < maxsum) dp2[sum] = max(dp2[sum], dp1[sum - obj[i - 1].second.first] + obj[i - 1].second.second);
        }
        dp1 = dp2;
    }
    cout << *max_element(dp1.begin(), dp1.end()) << '\n';
    return 0;
}