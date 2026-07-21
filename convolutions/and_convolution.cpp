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

template<class T> vc<T> and_zeta(vc<T> A){
    int N = 0;
    while (1 << N < len(A)) N++;
    for (int i = 0; i < N; i++){
        for (int S = 0; S < 1 << N; S++){
            if (~S & (1 << i)){
                A[S] += A[S ^ (1 << i)];
            }
        }
    }
    return A;
}

template<class T> vc<T> and_mebious(vc<T> A){
    int N = 0;
    while (1 << N < len(A)) N++;
    for (int i = 0; i < N; i++){
        for (int S = 0; S < 1 << N; S++){
            if (~S & (1 << i)){
                A[S] -= A[S ^ (1 << i)];
            }
        }
    }
    return A;
}

template<class T> vc<T> and_convolution(vc<T> &A, vc<T> &B){
    int length = 0;
    while (1 << length < len(A)) length++;
    while (1 << length < len(B)) length++;
    A.resize(1 << length);
    B.resize(1 << length);
    vc<T> zetaA = and_zeta(A), zetaB = and_zeta(B);
    for (int i = 0; i < 1 << length; i++) zetaA[i] *= zetaB[i];
    vc<T> ret = and_mebious(zetaA);
    return ret;
}

