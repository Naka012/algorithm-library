// (⁠◕⁠ᴗ⁠◕⁠✿⁠)
 
#include <bits/stdc++.h>
#define len(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
using namespace std;
template<typename T> using vc = vector<T>;
template<typename T> using vv = vc<vc<T>>;
using vi = vc<int>;using vvi = vv<int>; using vvvi = vv<vi>;
using ll = long long;using vl = vc<ll>;using vvl = vv<ll>; using vvvl = vv<vl>;
using ld = long double; using vld = vc<ld>; using vvld = vc<vld>; using vvvld = vc<vvld>;
using uint = unsigned int;
using ull = unsigned long long;
const double pi = 3.141592653589793;
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
// const ll mod = 1000000007;
const ll mod = 998244353;
inline bool inside(long long y, long long x, long long H, long long W) {return 0 <= y and y < H and 0 <= x and x < W; }

struct max_flow{
    public :
        max_flow(int N) : _n(N){
            g = vv<edge>(_n);
            level = vi(_n);
            iter = vi(_n);
        }

        void add_edge(int from, int to, ll cap){
            g[from].push_back((edge){to, cap, len(g[to])});
            g[to].push_back((edge){from, 0, len(g[from]) - 1});
        }

        void bfs(int s){
            deque<int> q;
            for (int i = 0; i < _n; i++) level[i] = -1;
            level[s] = 0;
            q.push_back(s);
            while (!q.empty()){
                int now = q.front(); q.pop_front();
                for (int i = 0; i < len(g[now]); i++){
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
            for (int &i = iter[v]; i < len(g[v]); i++){
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
        
        vc<bool> min_cut(int s){
            vc<bool> visited(_n);
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
        vv<edge> g;
        vi level, iter;
};
