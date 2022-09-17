#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m; cin >> n >> m;
    vector <int> col(n);
    string s; cin >> s;
    for (int i = 0; i < n; i++) col[i] = (s[i] == 'B');
    int ans = 0;
    for (int step = 1; 2 * step < n; step++) {
        int cur = 0;
        set <pair <int, pair <int, int>>> used;
        for (int j = 0; j < n; j++) {
            if (col[j] == col[(j + step) % n] && col[j] == col[(j + 2 * step) % n]) {
                int a = j, b = (j + step) % n, c = (j + 2 * step) % n;
                if (a > b) swap(a, b);
                if (a > c) swap(a, c);
                if (b > c) swap(b, c);
                used.insert({a, {b, c}});
            }
        }
        ans += used.size();
    }
    for (int i = 0; i < m; i++) {
        int id; cin >> id; id--;
        set <pair <int, pair <int, int>>> used;
        for (int step = 1; 2 * step < n; step++) {
            int a = (id + n - step) % n, b = id, c = (id + step) % n;
            if (a > b) swap(a, b);
            if (a > c) swap(a, c);
            if (b > c) swap(b, c);
            if (used.find({a, {b, c}}) == used.end()) {
                used.insert({a, {b, c}});
                if (col[id] == col[(id + n - step) % n] && col[id] == col[(id + step) % n]) ans--;
                if (col[id] != col[(id + n - step) % n] && col[id] != col[(id + step) % n]) ans++;
            }
            a = id, b = (id + step) % n, c = (id + 2 * step) % n;
            if (a > b) swap(a, b);
            if (a > c) swap(a, c);
            if (b > c) swap(b, c);
            if (used.find({a, {b, c}}) == used.end()) {
                used.insert({a, {b, c}});
                if (col[id] == col[(id + step) % n] && col[id] == col[(id + 2 * step) % n]) ans--;
                if (col[id] != col[(id + step) % n] && col[id] != col[(id + 2 * step) % n]) ans++;
            }
            a = (id + 2 * n - 2 * step) % n, b = (id + n - step) % n, c = id;
            if (a > b) swap(a, b);
            if (a > c) swap(a, c);
            if (b > c) swap(b, c);
            if (used.find({a, {b, c}}) == used.end()) {
                used.insert({a, {b, c}});
                if (col[id] == col[(id + 2 * n - 2 * step) % n] && col[id] == col[(id + n - step) % n]) ans--;
                if (col[id] != col[(id + 2 * n - 2 * step) % n] && col[id] != col[(id + n - step) % n]) ans++;
            }
        }
        col[id] = !col[id];
        cout << ans << '\n';
    }
    return 0;
}