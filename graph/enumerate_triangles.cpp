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
const ld pi = 3.141592653589793;
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
// const ll mod = 1000000007;
const ll mod = 998244353;
inline bool inside(long long y, long long x, long long H, long long W) {return 0 <= (y) and (y) < (H) and 0 <= (x) and (x) < (W); }

#define debug(var)  do{std::cout << #var << " : \n";view(var);}while(0)
template<typename T> void view(T e){cout << e << endl;}
template<typename T> void view(const vc<T>& v){for(const auto& e : v){ cout << e << " "; } cout << endl;}
template<typename T> void view(const vv<T>& vv){ for(const auto& v : vv){ view(v); } }

vc<tuple<int, int, int>> enumerate_triangles(vvi &g){
    vc<tuple<int, int, int>> ret;
    int N = len(g);
    vvi ng(N);
    for (int v = 0; v < N; v++) for (auto u : g[v]) if (make_pair(g[v].size(), v) < make_pair(g[u].size(), u)) ng[v].push_back(u);
    vi exist(N, 0);
    rep(a, N){
        for (auto x : ng[a]) exist[x] = 1;
        for (auto b : ng[a]) for (auto c : ng[b]) if (exist[c]) ret.push_back({a, b, c});
        for (auto x : ng[a]) exist[x] = 0;
    }
    return ret;
}
