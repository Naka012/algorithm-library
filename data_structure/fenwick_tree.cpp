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

template<class T> struct fenwick_tree {
    public : 
        fenwick_tree(int n) : _n(n) {
            tree = vc<T>(_n, 0);
        }
        
        void add(int p, T x){
            assert(0 <= p && p < _n);
            p++;
            while (p <= _n) {
                tree[p - 1] += x;
                p += p & -p;
            }
        }
        
        T sum_(int p){
            T ret = 0;
            while (p > 0){
                ret += tree[p - 1];
                p -= p & -p;
            }
            return ret;
        }
        
        T sum(int l, int r){
            assert(0 <= l && l < r && r <= _n);
            return sum_(r) - sum_(l);
        }
    private : 
        int _n;
        vc<T> tree;
};

