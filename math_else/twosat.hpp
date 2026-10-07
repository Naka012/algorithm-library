/*

two sat

add a(f) or b(g)
*/

struct twosat{
    public :
        twosat(int n) : nn(n){
            _n = 2 * nn;
            group = vector<int>(_n, -1);
            order = vector<int>();
            order.clear();
            g = vector<vector<int>>(_n);
            rg = vector<vector<int>>(_n);
            label = 0;
            answer = vector<bool>(nn);
        }

        void add_edge(int u, int v){
            g[u].push_back(v);
            rg[v].push_back(u);
        }

        void dfs(int s){
            used[s] = true;
            for (auto t : g[s]){
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

        void scc(){
            used = vector<bool>(_n);
            nused = vector<bool>(_n);
            for (int i = 0; i < _n; i++){
                if (!used[i]) dfs(i);
            }
            for (int i = (int)order.size() - 1; i >= 0; i--){
                if (!nused[order[i]]){
                    rdfs(order[i], label);
                    label++;
                }
            }
        }

        void add(int i, bool f, int j, bool g){
            add_edge(2 * i + (f ? 0 : 1), 2 * j + (g ? 1 : 0));
            add_edge(2 * j + (g ? 0 : 1), 2 * i + (f ? 1 : 0));
        }

        bool judge(){
            scc();
            for (int i = 0; i < nn; i++){
                if (group[2 * i] == group[2 * i + 1]) return false;
                answer[i] = group[2 * i] < group[2 * i + 1];
            }
            return true;
        }

        vector<bool> restore(){
            return answer;
        }
    
    private : 
        int _n, nn, label;
        vector<int> order, group;
        vector<vector<int>> g, rg;
        vector<bool> used, nused, answer;
};
