// https://github.com/Naka012/algorithm-library/blob/main/graph/dijkstra.hpp

/*
dijkstra
O(|E|log |V|)

Args:
    s (int) : start
    N (int) : |V|
    g (graph)

Returns:
    dist (vector<ll>) : dist[i] := s to i 's min cost
    bef (vector<int>) : bef[i] := path's before vertic

restore_path
O(|path|)

Args:
    start (int)
    goal (int)
    bef (vector<int>) : dijkstra's return

Returns:
    path (vector<int>) : path's ordered vertics numbers
*/

tuple<vector<ll>, vector<int>> dijkstra(int s, int N, vector<vector<pair<int, ll>>> &g){
    using P = pair<ll, int>;
    const ll INF = 0x3f3f3f3f3f3f3f3f;
    vector<ll> dist(N, INF);
    vector<int> bef(N);
    priority_queue<P, vector<P>, greater<P>> q;
    dist[s] = 0;
    q.push({0, s});
    while (!q.empty()){
        auto [c, now] = q.top();q.pop();
        if (dist[now] < c) continue;
        for (auto&& [nxt, nc]: g[now]) if (dist[nxt] > c + nc){
            dist[nxt] = c + nc;
            bef[nxt] = now;
            q.push({dist[nxt], nxt}); 
        }
    }
    return {dist, bef};
}

vector<int> restore_path_dj(int start, int goal, vector<int> &bef){
    vector<int> path;
    int now = goal;
    while (now != start){
        path.push_back(now);
        now = bef[now];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}
