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

template<class T, T (*op)(T, T), T (*e)()> struct dual_segtree{
    public : 
        dual_segtree(int n) : _n(n){
            depth = 0;
            while ((1 << depth) < _n) depth++;
            size = 1 << depth;
            tree = vc<T>(2 * size, e());
        }

        void set(int l, int r, T x){
            assert (0 <= l && l <= r && r <= _n);
            if (l == r) return;
            l += size;
            r += size;
            while(l < r){
                if (l & 1){
                    tree[l] = op(x, tree[l]);
                    l++;
                }
                if (r & 1){
                    r--;
                    tree[r] = op(x, tree[r]);
                }
                l >>= 1;
                r >>= 1;
            }
            return;
        }

        T get(int p){
            assert(0 <= p && p <= _n);
            p += size;
            T ret = e();
            while (p){
                ret = op(ret, tree[p]);
                p >>= 1;
            }
            return ret;
        }

    private : 
        int _n, depth, size;
        vc<T> tree;
};
