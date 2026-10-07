/*
warshall floyd
O(|V| ** 3)
Args:
    g (vector<vector<ll>>) : g[i][j] := cost of i to j
    N (int) : vertics number

Returns:
    nxt (vector<vector<int>>)

restore path
O(|path|)
Args:
    start (int)
    goal (int)
    nxt : warshall floyd 's return

Returns:
    path
*/

vector<vector<int>> warshall_floyd(vector<vector<ll>> &g, int &N){
    const ll INF = 0x3f3f3f3f3f3f3f3f;
    vector<vector<int>> bef(N); for (int i = 0; i < N; i++) bef[i] = vector<int>(N, i);
    for (int k = 0; k < N; k++) for (int i = 0; i < N; i++) for (int j = 0; j < N; j++){
        if (g[i][k] != INF && g[k][j] != INF){
            if (g[i][j] > g[i][k] + g[k][j]){
                g[i][j] = g[i][k] + g[k][j];
                bef[i][j] = bef[k][j];
            }
        }
    }
    return bef;
}

vector<int> restore_path_wf(int &start, int &goal, vector<vector<int>> &bef){
    vector<int> path = {goal};
    int now = goal;
    while (now != start){
        now = bef[start][now];
        path.push_back(now);
    }
    reverse(path.begin(), path.end());
    return path;
}
