int q; cin >> q;
    vector <pair <int, int>> days(q);
    for (auto& u : days) cin >> u.second >> u.first;
    sort(days.begin(), days.end());
    int ans = 0;
    for (int i = 0; i < q; i++) {
        int t = days[i].first, v = days[i].second, maxval = 0;
        for (auto [u, l] : dist[v]) {
            int cur = get_max(dp[u], 0, t - l);
            maxval = max(maxval, cur);
        }
        for (auto [u, l] : dist[v]) {
            insert(dp[u], t + l, maxval);
        }
        ans = max(ans, maxval);
    }
    cout << ans << '\n';