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

vc<bool> eratosthenes(int t){
    vc<bool> is_prime(t + 1, true);
    is_prime[0] = false; is_prime[1] = false;
    for (int i = 0; i <= t; i++){
        if (is_prime[i]){
            for (int q = i * 2; q <= t; q += i){
                is_prime[q] = false;
            }
        }
    }
    return is_prime;
}

template<class T> vc<T> multiple_zeta(vc<T> A, vc<bool> &is_prime){
    int N = len(A) - 1;
    for (int p = 0; p <= N; p++){
        if (is_prime[p]){
            for (int k = N / p; k > 0; --k){
                A[k] += A[k * p];
            }
        }
    }
    return A;
}

template<class T> vc<T> multiple_mebious(vc<T> A, vc<bool> &is_prime){
    int N = len(A) - 1;
    for (int p = 0; p <= N; p++){
        if (is_prime[p]){
            for (int k = 1; k * p <= N; ++k){
                A[k] -= A[k * p];
            }
        }
    }
    return A;
}

template<class T> vc<T> gcd_convolution(vc<T> &A, vc<T> &B){
    int length = max(len(A), len(B));
    vc<bool> is_prime = eratosthenes(length);
    A.resize(length); B.resize(length);
    vc<T> zetaA = multiple_zeta<T>(A, is_prime), zetaB = multiple_zeta<T>(B, is_prime);
    vc<T> cross(length);
    for (int i = 0; i < length; i++) cross[i] = zetaA[i] * zetaB[i];
    vc<T> ret = multiple_mebious<T>(cross, is_prime);
    return ret;
}

