int N;
vector<bool> used(N, false);

int dfs(int v, vector<vector<int>> &g, vector<int> &child){
    int ret = -1;
    child[v] = 0;
    bool flag = true;
    for (auto nxt : g[v]) if (child[nxt] == -1 && !used[nxt]){
        ret = max(ret, dfs(nxt, g, child));
        child[v] += child[nxt] + 1;
        if (child[nxt] > N / 2) flag = false;
    }
    if (N - child[v] - 1 > N / 2) flag = false;
    if (flag) ret = max(ret, v);
    return ret;
}

int centroid_decomposision(int s, vector<vector<int>> &g){
    vector<int> child(N, -1);
    return dfs(s, g, child);
    
}

int re_centroid_decomposision(int s, vector<vector<int>> &g){
    vector<int> child(N, -1);
    int center = dfs(s, g, child);
    used[center] = true;
    for (auto x : g[center]) re_centroid_decomposision(x, g);
}
