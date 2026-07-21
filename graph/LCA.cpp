// (⁠◕⁠ᴗ⁠◕⁠✿⁠)

#include <bits/stdc++.h>
#define rep(i, n) for (ll i = 0; i < (n); i++)
#define srep(i, s, n) for (ll i = s; i < (n); i++)
#define len(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
using namespace std;
template<typename T> using vc = vector<T>;
template<typename T> using vv = vc<vc<T>>;
template<typename T> using vvv = vv<vc<T>>;
using vi = vc<int>;using vvi = vv<int>; using vvvi = vv<vi>;
using ll = long long;using vl = vc<ll>;using vvl = vv<ll>; using vvvl = vv<vl>;
using ld = long double; using vld = vc<ld>; using vvld = vc<vld>; using vvvld = vc<vvld>;
using uint = unsigned int;
using ull = unsigned long long;
const ld pi = acos(-1.0);
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
// const ll mod = 1000000007;
const ll mod = 998244353;
inline bool inside(ll y, ll x, ll H, ll W) {return 0 <= (y) and (y) < (H) and 0 <= (x) and (x) < (W); }
 

struct LCA {
    public : 
        LCA(vvi &_g) : g(_g){
            int N = len(g);
            dbring.resize(20, vi(N));
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
        vvi dbring, g;
        vi depth, vol;
};
