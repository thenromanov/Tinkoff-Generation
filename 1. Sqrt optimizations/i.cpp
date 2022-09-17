#include <bits/stdc++.h>
using namespace std;

const int sqroot = 50;
const int sqroot3 = 2000;
const int MAXN = 1e5 + 7;

struct req {
    int version, l, r, index;
};

struct mex {
    int size;
    vector <int> value, count, block;

    mex(int size) {
        this->size = size;
        value.resize(2 * size);
        count.resize(size);
        block.resize((size - 1) / sqroot + 1);
    }

    void add(int x) {
        if (count[value[x]] == 1) block[value[x] / sqroot]--;
        count[value[x]]--;
        value[x]++;
        if (count[value[x]] == 0) block[value[x] / sqroot]++;
        count[value[x]]++;
    }

    void del(int x) {
        if (count[value[x]] == 1) block[value[x] / sqroot]--;
        count[value[x]]--;
        value[x]--;
        if (count[value[x]] == 0) block[value[x] / sqroot]++;
        count[value[x]]++;
    }

    int get() {
        if (block[0] - (count[0] > 0) < sqroot - 1) {
            int i = 1;
            while (count[i] > 0) i++;
            return i;
        }
        int i = 1;
        while (block[i] == sqroot) i++;
        i *= sqroot;
        while (count[i] > 0) i++;
        return i;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, q, version = 0, qnum = 0; cin >> n >> q;
    vector <int> arr(n);
    map <int, int> reorder;
    for (int i = 0, c; i < n; i++) {
        cin >> c;
        if (reorder.find(c) == reorder.end()) reorder[c] = reorder.size();
        arr[i] = reorder[c];
    }
    vector <req> queries;
    vector <pair <int, int>> next = {make_pair(0, 0)}, prev;
    for (int i = 0, c, l, r; i < q; i++) {
        cin >> c >> l >> r;
        if (c == 1) {
            queries.push_back({version, l - 1, r - 1, qnum++});
        } else {
            if (reorder.find(r) == reorder.end()) reorder[r] = reorder.size();
            next.push_back({l - 1, reorder[r]});
            version++;
        }
    }
    for (int i = 1; i < (int)next.size(); i++) {
        int l = next[i].first, r = next[i].second;
        prev.push_back({l, arr[l]});
        arr[l] = r;
    }
    prev.push_back({0, 0});
    for (int i = (int)prev.size() - 1; i > 0; i--) {
        int l = prev[i - 1].first, r = prev[i - 1].second;
        arr[l] = r;
    }
    sort(queries.begin(), queries.end(), [](req& a, req& b){
        if (a.version / sqroot3 == b.version / sqroot3) {
            if (a.l / sqroot3 == b.l / sqroot3) return (a.l / sqroot3 % 2 == 0 ? a.r < b.r : a.r > b.r);
            return a.l / sqroot3 < b.l / sqroot3;
        }
        return a.version / sqroot3 < b.version / sqroot3;
    });
    vector <int> ans((int)queries.size());
    int v = 0, l = 0, r = 0;
    mex inc(MAXN);
    inc.add(arr[0]);
    for (auto que : queries) {
        while (l > que.l){
            l--;
            inc.add(arr[l]);
        }
        while (r < que.r) {
            r++;
            inc.add(arr[r]);    
        }
        while (r > que.r) {
            inc.del(arr[r]);
            r--;
        }
        while (l < que.l) {
            inc.del(arr[l]);
            l++;
        }
        while (v < que.version) {
            v++;
            if (que.l <= next[v].first && next[v].first <= que.r) {
                inc.del(arr[next[v].first]);
                inc.add(next[v].second);
            }
            arr[next[v].first] = next[v].second;
        }
        while (v > que.version) {
            v--;
            if (que.l <= prev[v].first && prev[v].first <= que.r) {
                inc.del(arr[prev[v].first]);
                inc.add(prev[v].second);
            }
            arr[prev[v].first] = prev[v].second;
        }
        ans[que.index] = inc.get();
    }
    for (int u : ans) cout << u << '\n';
    return 0;
}