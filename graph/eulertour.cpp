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

/*
depth_euler : オイラーツアーの順番で回った時の頂点の深さの列
place : その頂点がdepthの何番目にいるか 必ず二つ入っている

*/

vi depth_euler;
map<int, vi> place;
vc<bool> seen(200200, false);
int depth = 0, cnt = 0;

void dfs(int v, vvi &g){
    seen[v] = true;
    depth_euler.push_back(depth);
    place[v].push_back(cnt);
    depth++;
    for(auto nxt : g[v]){
        if (!seen[nxt]){
            cnt++;
            dfs(nxt, g);
        }
    }
    depth--;
    cnt++;
    depth_euler.push_back(depth);
    place[v].push_back(cnt);
}
