#include <bits/stdc++.h>
#define len(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
using namespace std;
template<typename T> using vc = vector<T>;
template<typename T> using vv = vc<vc<T>>;
using vi = vc<int>;using vvi = vv<int>; using vvvi = vv<vc<int>>;
using ll = long long;using vl = vc<ll>;using vvl = vv<ll>;
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

/*
warshall floyd
O(|V| ** 3)
Args:
    g (vvl) : g[i][j] := cost of i to j
    N (int) : vertics number

Returns:
    nxt (vvi)

restore path
O(|path|)
Args:
    start (int)
    goal (int)
    nxt : warshall floyd 's return

Returns:
    path
*/

vvi warshall_floyd(vvl &g, int &N){
    vvi bef(N); for (int i = 0; i < N; i++) bef[i] = vi(N, i);
    for (int k = 0; k < N; k++) for (int i = 0; i < N; i++) for (int j = 0; j < N; j++){
        if (g[i][k] != INF && g[k][j] != INF){
            if (g[i][j] > g[i][k] + g[k][j]){
                g[i][j] = g[i][k] + g[k][j];
                bef[i][j] = bef[k][j];
            }
        }
    }
    return bef;
}

vi restore_path_wf(int &start, int &goal, vvi &bef){
    vi path = {goal};
    int now = goal;
    while (now != start){
        now = bef[start][now];
        path.push_back(now);
    }
    reverse(all(path));
    return path;
}

