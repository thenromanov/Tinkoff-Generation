#include <bits/stdc++.h>
using namespace std;

const vector <double> predict = {0.0817, 0.0149, 0.0278, 0.0425, 0.127, 0.0223, 0.0202, 0.0609, 0.0697, 0.0015, 0.0077, 0.0403, 0.0241, 0.0675, 0.0751, 0.0193, 0.001, 0.0599, 0.0633, 0.0906, 0.0276, 0.0098, 0.0236, 0.0015, 0.0197, 0.0007};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    vector <int> cnt(26);
    string s; int num = 0, c = 0;
    while (cin >> s) {
        for (auto u : s) {
            if (u >= 'A' && u <= 'Z') cnt[u - 'A']++, num++;
            else if (u >= 'a' && u <= 'z') cnt[u - 'a']++, num++;
        }
    }
    for (int i = 0; i < 26; i++) {
        if (fabs(cnt[i] - predict[i] * num) > num / 33.) c++;
    }
    cout << (c > 5 ? "Program\n" : "Petya\n");
    return 0;
}