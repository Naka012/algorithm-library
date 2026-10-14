// https://github.com/Naka012/algorithm-library/blob/main/graph/enumerate_triangles.hpp

vector<tuple<int, int, int>> enumerate_triangles(vector<vector<int>> &g){
    vector<tuple<int, int, int>> ret;
    int N = (int)g.size();
    vector<vector<int>> ng(N);
    for (int v = 0; v < N; v++) for (auto u : g[v]) if (make_pair(g[v].size(), v) < make_pair(g[u].size(), u)) ng[v].push_back(u);
    vector<int> exist(N, 0);
    rep(a, N){
        for (auto x : ng[a]) exist[x] = 1;
        for (auto b : ng[a]) for (auto c : ng[b]) if (exist[c]) ret.push_back({a, b, c});
        for (auto x : ng[a]) exist[x] = 0;
    }
    return ret;
}
