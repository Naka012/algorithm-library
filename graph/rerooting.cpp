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

/*
merge -> merge children
f1 -> (already merged -> parent can merge)
f2 -> to ans
*/

// using S = ll;
// using T = ;

// T merge(T a, T b){}
// T f1(T a, int u, int v, S cost){}
// T f2(T a, int v){}
// T e(){}
// T leaf(int){}

template <class S,
          class T,
          T (*merge)(T, T),
          T (*f1)(T, int, int, S),
          T (*f2)(T, int),
          T (*e)(),
          T (*leaf)(int)>
struct rerooting{
    public : 
        rerooting(vv<pair<int, S>> _g) : g(_g){
            N = len(g);
            acc1 = vc<T>(N, e());
            acc2 = vc<T>(N, e());
            res1 = vc<T>(N, e());
            res2 = vc<T>(N, e());
            acc_bef = vv<T>(N, {e()});
            acc_aft = vv<T>(N, {e()});
        }

        void dfs0(int v, int last = -1){
            vc<T> buildup;
            int cnt = 0;
            for (auto [u, c] : g[v]) if (u != last){
                cnt++;
                dfs0(u, v);
                res1[u] = f1(acc1[u], u, v, c);
                acc1[v] = merge(acc1[v], res1[u]);
                buildup.push_back(res1[u]);
            }
            if (cnt == 0) acc1[v] = leaf(v);
            for (int i = 0; i < len(buildup); i++) acc_bef[v].push_back(merge(acc_bef[v].back(), buildup[i]));
            for (int i = len(buildup) - 1; i >= 0; i--) acc_aft[v].push_back(merge(acc_aft[v].back(), buildup[i]));
        }

        void dfs1(int v, int last = -1){
            int w = 0;
            for (auto [u, c] : g[v]) if (u != last){
                acc2[u] = merge(merge(acc_bef[v][w], acc_aft[v][len(acc_aft[v]) - w - 2]), res2[v]);
                res2[u] = f1(acc2[u], v, u, c);
                dfs1(u, v);
                w++;
            }
        }

        vc<T> solve(){
            dfs0(0);
            dfs1(0);
            vc<T> ret(N);
            rep(v, N) ret[v] = f2(merge(acc1[v], res2[v]), v);
            return ret;
        }

    private : 
        int N;
        vv<pair<int, S>> g;
        vc<T> acc1, acc2, res1, res2;
        vv<T> acc_bef, acc_aft;
};
