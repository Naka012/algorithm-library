// (⁠◕⁠ᴗ⁠◕⁠✿⁠)
 
#include <bits/stdc++.h>
#define rep(i, n) for (ll i = 0; i < (int)(n); i++)
#define srep(i, s, n) for (ll i = s; i < (n); i++)
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

int N;
vc<bool> used(N, false);

int dfs(int v, vvi &g, vi &child){
    int ret = -1;
    child[v] = 0;
    bool flag = true;
    for (auto nxt : g[v]) if (child[nxt] == -1 && !used[nxt]){
        ret = max(ret, dfs(nxt, g, child));
        child[v] += child[nxt] + 1;
        if (child[nxt] > N / 2) flag = false;
    }
    if (N - child[v] - 1 > N / 2) flag = false;
    if (flag) ret = max(ret, v);
    return ret;
}

int centroid_decomposision(int s, vvi &g){
    vi child(N, -1);
    return dfs(s, g, child);
    
}

int re_centroid_decomposision(int s, vvi &g){
    vi child(N, -1);
    int center = dfs(s, g, child);
    used[center] = true;
    for (auto x : g[center]) re_centroid_decomposision(x, g);
}