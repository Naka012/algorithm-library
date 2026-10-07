struct LCA {
    public : 
        LCA(vector<vector<int>> &_g) : g(_g){
            int N = (int)g.size();
            dbring.resize(20, vector<int>(N));
            depth.resize(N);
            vol.resize(N, 1);
            dfs(0, 0);
            rep(k, 19) rep(i, N){
                if (dbring[k][i] == -1) dbring[k + 1][i] = -1;
                else dbring[k + 1][i] = dbring[k][dbring[k][i]];
            }
        }

        void dfs(int v, int d, int last = -1){
            dbring[0][v] = last;
            depth[v] = d;
            for (auto u : g[v]) if (u != last){
                dfs(u, d + 1, v);
                vol[v] += vol[u];
            }
        }

        int LA(int v, int h){
            for (int i = 19; i >= 0; i--) if (h >= (1 << i)){
                v = dbring[i][v];
                h -= 1 << i;
            }
            return v;
        }

        int query(int u, int v){
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

        int parent(int v){return dbring[0][v];}

        int volume(int v){return vol[v];}

    private :
        vector<vector<int>> dbring, g;
        vector<int> depth, vol;
};
