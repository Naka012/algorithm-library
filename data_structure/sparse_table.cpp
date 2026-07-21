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
sparse_table
(min max lcm gcd)
sparse_table<T, op, e> sp(int n)

型 T
二項演算 T op(T a, T b)
単位元 T e()

長さnの配列に対し、
build O(n log n)
prod O(1)

*/

template<class T, T (*op)(T, T), T (*e)()> struct sparse_table {
    public : 
        sparse_table(int n) : _n(n) {
            bits = 0;
            var = n;
            for (bits; var != 0; bits++) var >>= 1;
            table = vc<vc<T>>(n, vc<T>(bits + 1, e()));
        }

        void build(vc<T> &A) {
            assert(len(A) <= _n);
            for (int i = 0; i < _n; i++) table[i][0] = A[i];
            for (int k = 1; k < bits; k++){
                for (int i = 0; i < _n - (1 << k) + 1; i++){
                    table[i][k] = op(table[i][k - 1], table[i + (1 << (k - 1))][k - 1]);
                }
            }
            
        }

        T prod(int l, int r){
            assert(0 <= l && l < _n);
            assert(0 < r && r <= _n);
            int l2 = (int)log2(r - l);
            return op(table[l][l2], table[r - (1 << l2)][l2]);
        }

    private : 
        int _n, bits, var;
        vc<vc<T>> table;
};

template<class T, T (*op)(T, T), T (*e)()> struct sparse_table {
    public : 
        sparse_table(const vc<T> &A){
            _n = len(A);
            bits = 0;
            var = _n;
            for (bits; var != 0; bits++) var >>= 1;
            table = vc<vc<T>>(_n, vc<T>(bits + 1, e()));
            for (int i = 0; i < _n; i++) table[i][0] = A[i];
            for (int k = 1; k < bits; k++){
                for (int i = 0; i < _n - (1 << k) + 1; i++){
                    table[i][k] = op(table[i][k - 1], table[i + (1 << (k - 1))][k - 1]);
                }
            }
        }

        T prod(int l, int r){
            assert(0 <= l && l <= _n);
            assert(0 <= r && r <= _n);
            if (l == r) return e();
            int l2 = (int)log2(r - l);
            return op(table[l][l2], table[r - (1 << l2)][l2]);
        }

    private : 
        int _n, bits, var;
        vc<vc<T>> table;
};
