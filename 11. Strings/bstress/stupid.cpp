#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string s; getline(cin, s);
    set <string> st;
    for (int i = 0; i < (int)s.size(); i++) {
        string cur = s.substr(i, (int)s.size() - i) + s.substr(0, i);
        st.insert(cur);
    }
    int k; cin >> k; k--;
    if (k > (int)st.size() - 1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    auto it = st.begin();
    for (int i = 0; i < k; i++) it++;
    cout << *it << '\n';
    return 0;
}