#include <bits/stdc++.h>
using namespace std;

const int64_t maxa = 1e11;
const int maxn = 1e6;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int64_t a, b; cin >> a >> b;
    vector <int> p(maxn, 1);
    vector <int64_t> primes;
    for (int i = 2; i < maxn; i++) {
        if (p[i]) {
            primes.push_back(i);
            if (1LL * i * i < maxn) for (int j = i * i; j < maxn; j += i) p[j] = 0;
        }
    }
    vector <int64_t> good = {2, 3, 5, 7};
    unordered_map <int64_t, int64_t> pwr;
    pwr[2] = pwr[3] = pwr[5] = pwr[7] = 10;
    for (int k = 0; k < (int)good.size(); k++) {
        for (int i = 1; i < 10; i++) {
            int64_t cp = pwr[good[k]] * i + good[k];
            bool found = 0;
            if (cp < maxn) found = !p[cp];
            else {
                for (int i = 0; i < (int)primes.size() && primes[i] * primes[i] <= cp; i++) {
                    if (cp % primes[i] == 0) {
                        found = 1;
                        break;
                    }
                }
            }
            if (!found && cp < maxa) good.push_back(cp), pwr[cp] = pwr[good[k]] * 10;
        }
    }
    sort(good.begin(), good.end());
    good.erase(unique(good.begin(), good.end()), good.end());
    int cnta = lower_bound(good.begin(), good.end(), a) - good.begin(), cntb = upper_bound(good.begin(), good.end(), b) - good.begin();
    cout << max(0, cntb - cnta) << '\n';
    return 0;
}