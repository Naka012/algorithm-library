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
const ld pi = 3.141592653589793;
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
// const ll mod = 1000000007;
const ll mod = 998244353;

/*
hld.id(v) -> seg等に乗っけるidを返す
prod -> seg等で必要な区間の集合を返す
*/

struct HLD{
    public : 
        void hld_dfs1(int v){
            for (auto u : _g[v]) if (depth[u] == -1){
                depth[u] = depth[v] + 1;
                parent[u] = v;
                hld_dfs1(u);
                child[v] += child[u] + 1;
            }
        }

        void hld_dfs2(int v){
            int biggest = 0, id = -1;
            for (auto u : _g[v]) if (idx[u] == -1 && biggest < child[u] + 1){
                biggest = child[u] + 1;
                id = u;
            }
            if (id != -1){
                represent[id] = represent[v];
                idx[id] = cnt;
                cnt++;
                hld_dfs2(id);
                for (auto u : _g[v]) if (idx[u] == -1){
                    represent[u] = u;
                    idx[u] = cnt;
                    cnt++;
                    hld_dfs2(u);
                }
            }
        }

        HLD(int n, int s, vvi g) : _n(n){
            _s = s;
            _g = g;
            depth = vi(_n, -1);
            child = vi(_n, 0);
            parent = vi(_n, 0);
            idx = vi(_n, -1);
            represent = vi(_n, -1);
            represent[s] = s;
            depth[s] = 0;
            cnt = 1;
            idx[s] = 0;
            hld_dfs1(_s);
            hld_dfs2(_s);
        }

        int id(int v){return idx[v];}

        vc<pair<int, int>> prod(int u, int v){
            vc<pair<int, int>> ret;
            while (represent[u] != represent[v]){
                if (depth[represent[u]] > depth[represent[v]]) swap(u, v);
                ret.push_back({idx[represent[v]], idx[v] + 1});
                v = parent[represent[v]];
            }
            ret.push_back({min(idx[u], idx[v]), max(idx[u], idx[v]) + 1});
            return ret;
        }

    private : 
        int _n, _s, cnt;
        vvi _g;
        vi depth, child, parent, idx, represent;
};
