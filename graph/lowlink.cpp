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

struct lowlink {
    const vvi &g;
    vi parent, ord, low, ap, connected_comp_diff;
    vc<pair<int, int>> bridge;

    lowlink(const vvi &g_) : g(g_){
        parent.resize(len(g), -2);
        ord.resize(len(g), 0);
        low.resize(len(g), 0);
        connected_comp_diff.resize(len(g), 0);
        int k = 0;
        rep(v, len(g)) if (parent[v] == -2){
            parent[v] = -1;
            k = dfs(v, k);
        }
    }

    int dfs(int v, int k){
        bool flag = false;
        ord[v] = k++;
        low[v] = ord[v];
        int child = 0;
        for (auto u : g[v]){
            if (parent[u] == -2){
                child++;
                parent[u] = v;
                k = dfs(u, k);
                low[v] = min(low[v], low[u]);
                if (parent[v] != -1 && ord[v] <= low[u]){
                    connected_comp_diff[v]++;
                    flag = true;
                }
                if (ord[v] < low[u]) bridge.push_back({v, u});
            }else if (u != parent[v]){
                low[v] = min(low[v], ord[u]);
            }
        }
        if (parent[v] == -1) connected_comp_diff[v] = child - 1;
        // if ((parent[v] == -1 && len(g[v]) >= 2) || flag) ap.push_back(v);
        if (flag || (parent[v] == -1 && child > 1)) ap.push_back(v);
        return k;
    }
};
