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
dot
Args:
    A (vv(T))
    B (VV(T))
Returns:
    A * B (vv(T))

multidot
Args:
    A (vv(T))
    N (ll)
Returns:
    A ** N (vv(T))
*/

template<typename T> vc<vc<T>> dot(vc<vc<T>> &A, vc<vc<T>> &B){
    vc<vc<T>> ret;
    for (int i = 0; i < len(A); i++){
        vc<T> row;
        for (int j = 0; j < len(B[0]); j++){
            T ele = 0;
            for (int k = 0; k < len(A[0]); k++){
                ele += A[i][k] * B[k][j];
            }
            row.push_back(ele);
        }
        ret.push_back(row);
    }
    return ret;
}

template<typename T> vc<vc<T>> multidot(vc<vc<T>> &A, ll &N){
    vc<vc<T>> ret(len(A), vc<T>(len(A), 0));
    for (int i = 0; i < len(A); i++) ret[i][i] = 1;
    while (N > 0){
        if (N & 1) ret = dot(ret, A);
        A = dot(A, A);
        N >>= 1;
    }
    return ret;
}

