// (⁠◕⁠ᴗ⁠◕⁠✿⁠)

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")
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
const ld pi = 3.141592653589793;
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
// const ll mod = 1000000007;
const ll mod = 998244353;
inline bool inside(ll y, ll x, ll H, ll W) {return 0 <= (y) and (y) < (H) and 0 <= (x) and (x) < (W); }

#define debug(var)  do{std::cout << #var << " : \n";view(var);}while(0)
template<typename T> void view(T e){cout << e << endl;}
template<typename T> void view(const vc<T>& v){for(const auto& e : v){ cout << e << " "; } cout << endl;}
template<typename T> void view(const vv<T>& vv){ for(const auto& v : vv){ view(v); } }

struct ET {
    public : 
        ET(vvi _g) : g(_g){
            N = len(g);
            dbring = vvi(20, vi(N));
            depth = vi(N, 0);
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
        vvi dbring, g;
        vi depth;
};
