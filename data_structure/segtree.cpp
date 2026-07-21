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
segtree<ll , op, e> st(N);

*/

template<class T, T (*op)(T, T), T (*e)()> struct segtree{
    public : 
        segtree(int n) : _n(n){
            depth = 0;
            while ((1 << depth) < _n) depth++;
            size = 1 << depth;
            tree = vc<T>(2 * size, e());
        }

        void set(int p, T x){
            assert (0 <= p && p < _n);
            p += size;
            tree[p] = x;
            for (int i = 0; i < depth; i++){
                p >>= 1;
                tree[p] = op(tree[2 * p], tree[2 * p + 1]);
            }
            return;
        }

        T get(int p){
            assert(0 <= p && p < _n);
            return tree[p + size];
        }

        T prod(int l, int r){
            assert (0 <= l && l <= r && r <= _n);
            if (l == r) return e();
            T nl = e(), nr = e();
            l += size;
            r += size;
            while(l < r){
                if (l & 1) nl = op(nl, tree[l++]);
                // if (r & 1) nr = op(nr, tree[--r]);
                if (r & 1) nr = op(tree[--r], nr);
                l >>= 1;
                r >>= 1;
            }
            return op(nl, nr);
        }
    
    private : 
        int _n, depth, size;
        vc<T> tree;
};
