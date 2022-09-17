#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9 + 7;

struct p {
    int d, t = INT_MAX;
};

bool checkl(vector <p> v, int k, int t, int s) {
    int n = (int)v.size();
    double allt = 0;
    for (int i = k; i >= 0; i--) {
        for (int j = k + 1; j < n; j++) {
            double tmr = 0.5 * (v[j].d - v[i].d) / s;
            allt += tmr;
            if (v[j].t == INT_MAX && v[i].t != INT_MAX && tmr <= t && allt) v[j].t = v[i].t + tmr;
            if (v[i].t == INT_MAX && v[j].t != INT_MAX && tmr <= t) v[i].t = v[j].t + tmr;
        }
    }
    for (int i = 0; i < n; i++) {
        if (v[i].t == INT_MAX) return false;
    }
    return true;
}

bool checkr(vector <p> v, int k, int t, int s) {
    int n = (int)v.size();
    for (int i = k; i < n; i++) {
        for (int j = k - 1; j >= 0; j--) {
            double tmr = 0.5 * (v[i].d - v[j].d) / s;
            if (v[i].t == INT_MAX && v[j].t != INT_MAX && tmr <= t) v[i].t = v[j].t + tmr;
            if (v[j].t == INT_MAX && v[i].t != INT_MAX && tmr <= t) v[j].t = v[i].t + tmr;
        }
    }
    for (int i = 0; i < n; i++) {
        if (v[i].t == INT_MAX) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, k, t; cin >> n >> k >> t;
    vector <p> v(n);
    for (int i = 0; i < n; i++) cin >> v[i].d;
    v[k - 1].t = 0;
    int l = 0, r = 1e9 + 7;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        if (checkl(v, k - 1, t, m) || checkr(v, k - 1, r, m)) r = m;
        else l = m;
    }
    cout << r << '\n';
    return 0;
}