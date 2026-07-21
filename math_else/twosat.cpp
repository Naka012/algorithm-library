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

two sat

add a(f) or b(g)
*/

struct twosat{
    public :
        twosat(int n) : nn(n){
            _n = 2 * nn;
            group = vi(_n, -1);
            order = vi();
            order.clear();
            g = vvi(_n);
            rg = vvi(_n);
            label = 0;
            answer = vc<bool>(nn);
        }

        void add_edge(int u, int v){
            g[u].push_back(v);
            rg[v].push_back(u);
        }

        void dfs(int s){
            used[s] = true;
            for (auto t : g[s]){
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

        void scc(){
            used = vc<bool>(_n);
            nused = vc<bool>(_n);
            for (int i = 0; i < _n; i++){
                if (!used[i]) dfs(i);
            }
            for (int i = len(order) - 1; i >= 0; i--){
                if (!nused[order[i]]){
                    rdfs(order[i], label);
                    label++;
                }
            }
        }

        void add(int i, bool f, int j, bool g){
            add_edge(2 * i + (f ? 0 : 1), 2 * j + (g ? 1 : 0));
            add_edge(2 * j + (g ? 0 : 1), 2 * i + (f ? 1 : 0));
        }

        bool judge(){
            scc();
            for (int i = 0; i < nn; i++){
                if (group[2 * i] == group[2 * i + 1]) return false;
                answer[i] = group[2 * i] < group[2 * i + 1];
            }
            return true;
        }

        vc<bool> restore(){
            return answer;
        }
    
    private : 
        int _n, nn, label;
        vi order, group;
        vvi g, rg;
        vc<bool> used, nused, answer;
};

