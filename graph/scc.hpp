/*
scc : 強連結成分分解
add : 辺追加
    Args :
        int u and int v : edge of u -> v
    Returns :
        none

build : 強連結成分分解
    Args:
        none
    Returns:
        int and vector<int>:グループ数 各頂点のラベル番号

construct : 縮約後のグラフ作成
    Args:
        label (int): sccの成分数
        group (vector<int>): sccのoutput
    Returns:
        vector<set<int>> and vector<vector<int>> : 新しいグラフの隣接リスト グラフのi番目に含まれる元々の頂点達
*/

struct scc {
    public : 
        scc(int n) : _n(n){
            order = vector<int>(); order.clear();
            group = vector<int>(_n, -1);
            g = vector<vector<int>>(_n);
            rg = vector<vector<int>>(_n);
        }

        void add(int &u, int &v){
            g[u].push_back(v);
            rg[v].push_back(u);
        }

        void dfs(int s){
            used[s] = true;
            for (auto  t : g[s]){
                if (!used[t]) dfs(t);
            }
            order.push_back(s);
        }

        void rdfs(int s, int color){
            group[s] = color;
            nused[s] = true;
            for (auto t : rg[s]){
                if (!nused[t]) rdfs(t, color);
            }
        }

        tuple<int , vector<int>> build(){
            used = vector<bool>(_n);
            nused = vector<bool>(_n);
            for (int i = 0; i < _n; i++){
                if (!used[i]) dfs(i);
            }
            int label = 0;
            for (int i = (int)order.size() - 1; i >= 0; i--){
                if (!nused[order[i]]){
                    rdfs(order[i], label);
                    label++;
                }
            }
            return {label, group};
        }

        tuple<vector<set<int>>, vector<vector<int>>> construct(int &label, vector<int> &group){
            vector<set<int>> ng(label);
            vector<vector<int>> gp(label);
            for (int v = 0; v < _n; v++){
                int lbv = group[v];
                for (auto w : g[v]){
                    int lbw = group[w];
                    if (lbv == lbw) continue;
                    ng[lbv].insert(lbw);
                }
                gp[lbv].push_back(v);
            }
            return {ng, gp};
        }

    private : 
        int _n;
        vector<int> order, group;
        vector<bool> used, nused;
        vector<vector<int>> g, rg;
};
