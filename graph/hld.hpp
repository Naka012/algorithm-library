// https://github.com/Naka012/algorithm-library/blob/main/graph/hld.hpp

/*
hld.id(v) -> seg等に乗っけるidを返す
prod -> seg等で必要な区間の集合を返す
*/

struct HLD{
    public : 
        void hld_dfs1(int v){
            for (auto u : _g[v]) if (depth[u] == -1){
                depth[u] = depth[v] + 1;
                parent[u] = v;
                hld_dfs1(u);
                child[v] += child[u] + 1;
            }
        }

        void hld_dfs2(int v){
            int biggest = 0, id = -1;
            for (auto u : _g[v]) if (idx[u] == -1 && biggest < child[u] + 1){
                biggest = child[u] + 1;
                id = u;
            }
            if (id != -1){
                represent[id] = represent[v];
                idx[id] = cnt;
                cnt++;
                hld_dfs2(id);
                for (auto u : _g[v]) if (idx[u] == -1){
                    represent[u] = u;
                    idx[u] = cnt;
                    cnt++;
                    hld_dfs2(u);
                }
            }
        }

        HLD(int n, int s, vector<vector<int>> g) : _n(n){
            _s = s;
            _g = g;
            depth = vector<int>(_n, -1);
            child = vector<int>(_n, 0);
            parent = vector<int>(_n, 0);
            idx = vector<int>(_n, -1);
            represent = vector<int>(_n, -1);
            represent[s] = s;
            depth[s] = 0;
            cnt = 1;
            idx[s] = 0;
            hld_dfs1(_s);
            hld_dfs2(_s);
        }

        int id(int v){return idx[v];}

        vector<pair<int, int>> prod(int u, int v){
            vector<pair<int, int>> ret;
            while (represent[u] != represent[v]){
                if (depth[represent[u]] > depth[represent[v]]) swap(u, v);
                ret.push_back({idx[represent[v]], idx[v] + 1});
                v = parent[represent[v]];
            }
            ret.push_back({min(idx[u], idx[v]), max(idx[u], idx[v]) + 1});
            return ret;
        }

    private : 
        int _n, _s, cnt;
        vector<vector<int>> _g;
        vector<int> depth, child, parent, idx, represent;
};
