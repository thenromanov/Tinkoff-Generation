#include <bits/stdc++.h>
using namespace std;

pair <int, int> intersect(const pair <int, int>& a, const pair <int, int>& b) {
    return {max(a.first, b.first), min(a.second, b.second)};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string s; cin >> s;
    int n = (int)s.size();
    vector <int> zero, one;
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') zero.push_back(i);
        else if (s[i] == '1') one.push_back(i);
    }
    int besta = -1, bestb = -1, bestsum = -1;
    for (int sum = 1; sum <= n; sum++) {
        pair <int, int> seg = {0, sum - 1};
        for (int l = 0; l < n; l += sum) {
            int r = l + sum - 1;
            pair <int, int> cur;
            auto zero_it = upper_bound(zero.begin(), zero.end(), r);
            auto one_it = lower_bound(one.begin(), one.end(), l);
            if (zero_it == zero.begin() || *prev(zero_it) < l) {
                if (one_it == one.end() || *one_it > r) continue;
                cur = {r - *one_it + 1, sum - 1};
            } else {
                zero_it--;
                if (one_it == one.end() || *one_it > r) cur = {0, r - *zero_it};
                else {
                    if (*zero_it > *one_it) cur = {0, -1};
                    else cur = {r - *one_it + 1, r - *zero_it};
                }
            }
            seg = intersect(seg, cur);
            if (seg.first > seg.second) break;
        }
        if (seg.first <= seg.second) {
            int b = seg.second;
            int a = sum - b;
            int last_block = (n - 1) / sum;
            int last_l = sum * last_block;
            int last_len = n - last_l;
            int black_sum = last_block * b + max(last_len - a, 0);
            if (black_sum > bestsum) {
                bestsum = black_sum;
                besta = a;
                bestb = b;
            }
        }
    }
    if (bestb == -1) {
        cout << -1 << '\n';
        return 0;
    }
    bestsum = besta + bestb;
    for (int l = 0; l < n; l += bestsum) {
        int r = min(l + bestsum - 1, n - 1);
        for (int i = l; i <= r; i++) {
            if (i < l + besta) cout << '0';
            else cout << '1';
        }
    }
    return 0;
}