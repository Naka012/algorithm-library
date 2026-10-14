// https://github.com/Naka012/algorithm-library/blob/main/graph/euler_tour.hpp

struct ET {
    public : 
        ET(vector<vector<int>> _g) : g(_g){
            N = (int)g.size();
            dbring = vector<vector<int>>(20, vector<int>(N));
            depth = vector<int>(N, 0);
            int cnt = 0;
            function<void(int, int)> dfs = [&](int v, int last){
                dbring[0][v] = last;
                for (auto u : g[v]) if (u != last){
                    depth[u] = depth[v] + 1;
                    dfs(u, v);
                }
            };
            dfs(0, 0);
            rep(v, N) rep(k, 19) dbring[k + 1][v] = dbring[k][dbring[k][v]];
        }
        
        int LA(int &v, int h){
            for (int i = 19; i >= 0; i--) if (h >= (1 << i)){
                v = dbring[i][v];
                h -= 1 << i;
            }
            return v;
        }

        int LCA(int u, int v){
            if (depth[u] < depth[v]) swap(u, v);
            u = LA(u, depth[u] - depth[v]);
            if (u == v) return u;
            for (int i = 19; i >= 0; i--){
                if (dbring[i][u] != dbring[i][v]){
                    u = dbring[i][u];
                    v = dbring[i][v];
                }
            }
            return dbring[0][u];
        }

        int dep(int v){return depth[v];}
    private :
        int N;
        vector<vector<int>> dbring, g;
        vector<int> depth;
};
