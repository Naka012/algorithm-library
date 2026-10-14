// https://github.com/Naka012/algorithm-library/blob/main/graph/biconnectedcomponent.hpp

struct BiconnectedComponent {
    vector<int> ord, low;
    vector<int> used;
    vector<vector<int>> g;
    vector<vector<pair<int, int>>> bc;
    vector<pair<int, int>> tmp;
    int n, k = 0;
    BiconnectedComponent(const vector<vector<int>> &g) : g(g) {
        n = g.size();
        ord.resize(n, -1);
        low.resize(n, -1);
        used.resize(n, 0);
        dfs(0, -1);
    }
    void dfs(int u, int prev) {
        used[u] = true;
        ord[u] = k++;
        low[u] = ord[u];
        int cnt = 0;
        for (auto v : g[u]) if (v != prev) {
            if (ord[v] < ord[u]) { 
                tmp.emplace_back(minmax(u, v));
            }
            if (!used[v]){
                cnt++;
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] >= ord[u]) {
                    bc.push_back({});
                    while (true) {
                        auto e = tmp.back();
                        bc.back().emplace_back(e);
                        tmp.pop_back();
                        if (min(u, v) == e.first && max(u, v) == e.second) {
                            break;
                        }
                    }
                }
            }else{
                low[u] = min(low[u], ord[v]);
            }
        }
    }
};
