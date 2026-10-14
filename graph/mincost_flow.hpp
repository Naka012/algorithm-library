// https://github.com/Naka012/algorithm-library/blob/main/graph/mincost_flow.hpp

struct mincost_flow{
    public : 
        static constexpr ll INF = 0x3f3f3f3f3f3f3f3f;

        mincost_flow(int n) : _n(n){
            g = vector<vector<edge>>(_n);
            dist = vector<ll>(_n, INF);
            prevv = vector<int>(_n);
            preve = vector<int>(_n);
        }

        void add_edge(int from, int to, ll cap, ll cost){
            g[from].push_back((edge){to, cap, cost, (int)g[to].size()});
            g[to].push_back((edge){from, 0, -cost, (int)g[from].size() - 1});
        }

        ll flow(int s, int t, ll f){
            ll ret = 0;
            while (f > 0){
                rep(i, _n) dist[i] = INF;
                dist[s] = 0;
                bool update = true;
                while (update){
                    update = false;
                    rep(v, _n){
                        if (dist[v] == INF) continue;
                        int i = 0;
                        for (auto &e : g[v]){
                            if (e.cap > 0 && dist[e.to] > dist[v] + e.cost){
                                dist[e.to] = dist[v] + e.cost;
                                prevv[e.to] = v;
                                preve[e.to] = i;
                                update = true;
                            }
                            i++;
                        }
                    }
                }
                if (dist[t] == INF) return INF;
                ll d = f;
                for (int v = t; v != s; v = prevv[v]) d = min(d, g[prevv[v]][preve[v]].cap);
                f -= d;
                ret += d * dist[t];
                for (int v = t; v != s; v = prevv[v]){
                    edge& e = g[prevv[v]][preve[v]];
                    e.cap -= d;
                    g[v][e.rev].cap += d;
                }
            }
            return ret;
        }

    private : 
        struct edge {int to; ll cap, cost; int rev;};
        int _n;
        vector<vector<edge>> g;
        vector<ll> dist;
        vector<int> prevv, preve;
};
