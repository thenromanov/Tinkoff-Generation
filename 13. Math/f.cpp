#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    vector <int> to(n), used(n), need(n);
    for (int i = 0, a; i < n; i++) {
        cin >> a; a--;
        to[a] = i;
    }
    for (int i = 0, b; i < n; i++) {
        cin >> b; b--;
        need[b] = i;
    }
    vector <int> ord, nord, was(n + 1, -1), prev(n + 1);
    for (int i = 2; i <= n; i++) {
        if (!prev[i]) {
            for (int j = i; j <= n; j += i) prev[j] = i;
        }
    }
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            ord.clear();
            nord.clear();
            int cur = i;
            while (!used[cur]) {
                used[cur] = 1;
                ord.push_back(cur);
                nord.push_back(need[cur]);
                cur = to[cur];
            }
            int s = -1, n = (int)ord.size();
            for (int j = 0; j < n; j++) {
                if (nord[j] == ord[0]) s = j;
            }
            if (s == -1) {
                cout << "No\n";
                return 0;
            }
            for (int j = 0; j < n; j++) {
                if (ord[j] != nord[(s + j) % n]) {
                    cout << "No\n";
                    return 0;
                }
            }
            while (n > 1) {
                int prv = prev[n], ml = 1;
                while (prev[n] == prv) {
                    n /= prv;
                    ml *= prv;
                    int sv = s % ml;
                    if (was[ml] != -1 && was[ml] != sv) {
                        cout << "No\n";
                        return 0;
                    }
                    was[ml] = sv;
                }
            }
        }
    }
    cout << "Yes\n";
    return 0;
}