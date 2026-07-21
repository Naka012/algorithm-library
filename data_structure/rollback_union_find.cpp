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
// const ll mod = 1000000007;
const ll mod = 998244353;


struct RollbackUnionFind{
    public : 
        RollbackUnionFind(int n) : _n(n){
            root = vi(_n, -1);
        }

        int find(int x){
            if (root[x] < 0) return x;
            return find(root[x]);
        }

        void unite(int x, int y){
            x = find(x);
            y = find(y);
            history.push_back({x, root[x]});
            history.push_back({y, root[y]});
            if (x != y){
                if (-root[x] < -root[y]) swap(x, y);
                root[x] += root[y];
                root[y] = x;
            }
        }

        bool same(int x, int y){
            return find(x) == find(y);
        }

        int size(int x){
            return -root[find(x)];
        }

        void undo(){
            root[history.back().first] = history.back().second;
            history.pop_back();
            root[history.back().first] = history.back().second;
            history.pop_back();
        }

        int nw(){
            return len(history) >> 1;
        }

        void snapshot(){
            sp = nw();
        }

        void rollback(int t = -1){
            if (t == -1) t = sp;
            while (nw() > t) undo();
        }

    private : 
        int _n, sp;
        vi root;
        vc<pair<int, int>> history;
};
