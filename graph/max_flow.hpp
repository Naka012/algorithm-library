struct max_flow{
    public :
        max_flow(int N) : _n(N){
            g = vector<vector<edge>>(_n);
            level = vector<int>(_n);
            iter = vector<int>(_n);
        }

        void add_edge(int from, int to, ll cap){
            g[from].push_back((edge){to, cap, (int)g[to].size()});
            g[to].push_back((edge){from, 0, (int)g[from].size() - 1});
        }

        void bfs(int s){
            deque<int> q;
            for (int i = 0; i < _n; i++) level[i] = -1;
            level[s] = 0;
            q.push_back(s);
            while (!q.empty()){
                int now = q.front(); q.pop_front();
                for (int i = 0; i < (int)g[now].size(); i++){
                    edge &e = g[now][i];
                    if (e.cap > 0 && level[e.to] < 0){
                        level[e.to] = level[now] + 1;
                        q.push_back(e.to);
                    }
                }
            }
        }

        ll dfs(int v, int t, ll f){
            if (v == t) return f;
            for (int &i = iter[v]; i < (int)g[v].size(); i++){
                edge &e = g[v][i];
                if (e.cap > 0 && level[v] < level[e.to]){
                    ll d = dfs(e.to, t, min(f, e.cap));
                    if (d > 0){
                        e.cap -= d;
                        g[e.to][e.rev].cap += d;
                        return d;
                    }
                }
            }
            return 0;
        }

        ll flow(int s, int t){
            const ll INF = 0x3f3f3f3f3f3f3f3f;
            ll flw = 0;
            while (true){
                bfs(s);
                if (level[t] < 0) return flw;
                for (int i = 0; i < _n; i++) iter[i] = 0;
                ll f;
                while ((f = dfs(s, t, INF)) > 0){
                    flw += f;
                }
            }
        }
        
        vector<bool> min_cut(int s){
            vector<bool> visited(_n);
            deque<int> q;
            q.push_back(s);
            while (!q.empty()){
                int p = q.front(); q.pop_front();
                visited[p] = true;
                for (auto e : g[p]) if (e.cap && !visited[e.to]){
                    visited[e.to] = true;
                    q.push_back(e.to);
                }
            }
            return visited;
        }
    private :
        int _n;
        struct edge{ int to; ll cap, rev;};
        vector<vector<edge>> g;
        vector<int> level, iter;
};
