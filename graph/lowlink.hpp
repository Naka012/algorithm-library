// https://github.com/Naka012/algorithm-library/blob/main/graph/lowlink.hpp

struct lowlink {
    const vector<vector<int>> &g;
    vector<int> parent, ord, low, ap, connected_comp_diff;
    vector<pair<int, int>> bridge;

    lowlink(const vector<vector<int>> &g_) : g(g_){
        parent.resize((int)g.size(), -2);
        ord.resize((int)g.size(), 0);
        low.resize((int)g.size(), 0);
        connected_comp_diff.resize((int)g.size(), 0);
        int k = 0;
        rep(v, (int)g.size()) if (parent[v] == -2){
            parent[v] = -1;
            k = dfs(v, k);
        }
    }

    int dfs(int v, int k){
        bool flag = false;
        ord[v] = k++;
        low[v] = ord[v];
        int child = 0;
        for (auto u : g[v]){
            if (parent[u] == -2){
                child++;
                parent[u] = v;
                k = dfs(u, k);
                low[v] = min(low[v], low[u]);
                if (parent[v] != -1 && ord[v] <= low[u]){
                    connected_comp_diff[v]++;
                    flag = true;
                }
                if (ord[v] < low[u]) bridge.push_back({v, u});
            }else if (u != parent[v]){
                low[v] = min(low[v], ord[u]);
            }
        }
        if (parent[v] == -1) connected_comp_diff[v] = child - 1;
        // if ((parent[v] == -1 && (int)g[v].size() >= 2) || flag) ap.push_back(v);
        if (flag || (parent[v] == -1 && child > 1)) ap.push_back(v);
        return k;
    }
};
