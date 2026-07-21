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
using pii = pair<int, int>;
const double pi = 3.141592653589793;
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
// const int mod = 1000000007;
const int mod = 998244353;
inline bool inside(long long y, long long x, long long H, long long W) {return 0 <= y and y < H and 0 <= x and x < W; }

/*
scc : 強連結成分分解
add : 辺追加
    Args :
        int u and int v : edge of u -> v
    Returns :
        none

build : 強連結成分分解
    Args:
        none
    Returns:
        int and vi:グループ数 各頂点のラベル番号

construct : 縮約後のグラフ作成
    Args:
        label (int): sccの成分数
        group (vi): sccのoutput
    Returns:
        vc<set<int>> and vvi : 新しいグラフの隣接リスト グラフのi番目に含まれる元々の頂点達
*/

struct scc {
    public : 
        scc(int n) : _n(n){
            order = vi(); order.clear();
            group = vi(_n, -1);
            g = vvi(_n);
            rg = vvi(_n);
        }

        void add(int &u, int &v){
            g[u].push_back(v);
            rg[v].push_back(u);
        }

        void dfs(int s){
            used[s] = true;
            for (auto  t : g[s]){
                if (!used[t]) dfs(t);
            }
            order.push_back(s);
        }

        void rdfs(int s, int color){
            group[s] = color;
            nused[s] = true;
            for (auto t : rg[s]){
                if (!nused[t]) rdfs(t, color);
            }
        }

        tuple<int , vi> build(){
            used = vc<bool>(_n);
            nused = vc<bool>(_n);
            for (int i = 0; i < _n; i++){
                if (!used[i]) dfs(i);
            }
            int label = 0;
            for (int i = len(order) - 1; i >= 0; i--){
                if (!nused[order[i]]){
                    rdfs(order[i], label);
                    label++;
                }
            }
            return {label, group};
        }

        tuple<vc<set<int>>, vvi> construct(int &label, vi &group){
            vc<set<int>> ng(label);
            vvi gp(label);
            for (int v = 0; v < _n; v++){
                int lbv = group[v];
                for (auto w : g[v]){
                    int lbw = group[w];
                    if (lbv == lbw) continue;
                    ng[lbv].insert(lbw);
                }
                gp[lbv].push_back(v);
            }
            return {ng, gp};
        }

    private : 
        int _n;
        vi order, group;
        vc<bool> used, nused;
        vvi g, rg;
};

