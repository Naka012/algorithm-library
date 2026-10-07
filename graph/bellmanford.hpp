vector<ll> bellmanford(int s, int N, vector<vector<pair<int, ll>>> &g){
    const ll INF = 0x3f3f3f3f3f3f3f3f;
    vector<ll> dist(N, INF);
    dist[s] = 0;
    rep(i, N - 1){
        rep(u, N) for (auto [v, w] : g[u]) if (dist[u] != INF && dist[v] > dist[u] + w){
            dist[v] = dist[u] + w;
        }
    }
    rep(i, N - 1){
        rep(u, N) for (auto [v, w] : g[u]) if (dist[u] != INF && dist[v] > dist[u] + w){
            dist[v] = -INF;
        }
    }
    return dist;
}
