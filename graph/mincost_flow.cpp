// (⁠◕⁠ᴗ⁠◕⁠✿⁠)

#include <bits/stdc++.h>
// #include <atcoder/all>
// using namespace atcoder;
// using mint = modint1000000007;
// using mint = modint998244353;
// using vmint = vc<mint>;using vvmint = vc<vmint>;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define srep(i, s, n) for (int i = s; i < n; i++)
#define drep(i, n) for (int i = n; i >= 0; i--)
#define dsrep(i, s, n) for (int i = s; i >= n; i--)
#define len(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define YES(n) cout << ((n) ? "YES" : "NO" ) << endl
#define Yes(n) cout << ((n) ? "Yes" : "No" ) << endl
using namespace std;
template<typename T> using vc = vector<T>;
template<typename T> using vv = vc<vc<T>>;
using vi = vc<int>;using vvi = vv<int>; using vvvi = vv<vi>;
using ll = long long;using vl = vc<ll>;using vvl = vv<ll>; using vvvl = vv<vl>;
using ld = long double; using vld = vc<ld>; using vvld = vc<vld>; using vvvld = vc<vvld>;
using uint = unsigned int;
using ull = unsigned long long;
using pii = pair<int, int>;
const double pi = 3.141592653589793;
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
// const int mod = 1000000007;
const int mod = 998244353;
inline bool inside(long long y, long long x, long long H, long long W) {return 0 <= y and y < H and 0 <= x and x < W; }

struct phash{
    inline size_t operator()(const pair<int,int> & p) const{
        const auto h1 = hash<int>()(p.first);
        const auto h2 = hash<int>()(p.second);
        return h1 ^ (h2 << 1);
    }
};

// int
struct mincost_flow{
    public : 
        mincost_flow(int n) : _n(n){
            g = vv<edge>(_n);
            dist = vi(_n, inf);
            prevv = vi(_n);
            preve = vi(_n);
        }

        void add_edge(int from, int to, int cap, int cost){
            g[from].push_back((edge){to, cap, cost, len(g[to])});
            g[to].push_back((edge){from, 0, -cost, len(g[from]) - 1});
        }

        int flow(int s, int t, int f){
            int ret = 0;
            while (f > 0){
                rep(i, _n) dist[i] = inf;
                dist[s] = 0;
                bool update = true;
                while (update){
                    update = false;
                    rep(v, _n){
                        if (dist[v] == inf) continue;
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
                if (dist[t] == inf) return -1;
                int d = f;
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
        struct edge {int to, cap, cost, rev;};
        int _n;
        vv<edge> g;
        vi dist, prevv, preve;
};

// ll
struct mincost_flow{
    public : 
        mincost_flow(int n) : _n(n){
            g = vv<edge>(_n);
            dist = vl(_n, INF);
            prevv = vi(_n);
            preve = vi(_n);
        }

        void add_edge(int from, int to, ll cap, ll cost){
            g[from].push_back((edge){to, cap, cost, len(g[to])});
            g[to].push_back((edge){from, 0, -cost, len(g[from]) - 1});
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
        vv<edge> g;
        vl dist;
        vi prevv, preve;
};
