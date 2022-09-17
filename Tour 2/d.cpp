#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    vector <int> l, r;
    string lft, rgh; cin >> lft >> rgh;
    for (auto u : lft) l.push_back(u - 'a');
    for (auto u : rgh) r.push_back(u - 'a');
    int lleq = l.front() * 
    return 0;
}