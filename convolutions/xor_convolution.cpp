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

template<class T> vc<T> Hadamard_Transform(vc<T> &A){
    int L = len(A);
    T h = 1;
    rep(_, L){
        for (int i = 0; i < L; i += h * 2) srep(j, i, i + h){
            A[j] = A[j] + A[j + h];
            A[j + h] = A[j] - A[j + h];
        }
        h *= 2;
    }
}

template<class T> vc<T> xor_convolution(vc<T> &A, vc<T> &B){
    int N = max(len(A), len(B)), bit = 0;
    while (N > 0){
        N >>= 1;
        bit++;
    }
    A.resize(1 << bit, 0);
    B.resize(1 << bit, 0);
    Hadamard_Transform(A);
    Hadamard_Transform(B);
    rep(i, 1 << bit) A[i] *= B[i];
    Hadamard_Transform(A);
    rep(i, 1 << bit) A[i] >>= bit;
    return A;
}
