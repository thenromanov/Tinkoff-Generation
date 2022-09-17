#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    vector <int> v = {19, 20, 21, 41, 42, 43};
    int cnt = 0;
    do {
        bool a = 1;
        for (int i = 1; i < 6; i++) if (v[i] - v[i - 1] > 18) a = 0;
        if (a) {
            for (int i = 0; i < 6; i++) cout << v[i] << ' ';
            cout << '\n';
            cnt++;
        }
    } while (next_permutation(v.begin(), v.end()));
    cout << cnt;
    return 0;
}