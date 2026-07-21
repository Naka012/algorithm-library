// (⁠◕⁠ᴗ⁠◕⁠✿⁠)
 
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
inline bool inside(long long y, long long x, long long H, long long W) {return 0 <= (y) and (y) < (H) and 0 <= (x) and (x) < (W); }

#define debug(var)  do{std::cout << #var << " : \n";view(var);}while(0)
template<typename T> void view(T e){cout << e << endl;}
template<typename T> void view(const vc<T>& v){for(const auto& e : v){ cout << e << " "; } cout << endl;}
template<typename T> void view(const vv<T>& vv){ for(const auto& v : vv){ view(v); } }

//重複組み合わせ [0, N) の数 選ぶ個数はlen(A)に依存

bool next_homogeneous_product(int N, vi &A){
    int k = len(A);
    rep(i, k - 1) if (A[i] < A[i + 1]){
        A[i]++;
        rep(j, i) A[j] = 0;
        return true;
    }
    if (A[k - 1] < N - 1){
        A[k - 1]++;
        rep(i, k - 1) A[i] = 0;
        return true;
    }
    return false;
}

//組み合わせ [0, N) の数 選ぶ個数はlen(A)に依存

bool next_combination(int N, vi &P){
    int k = len(P);
    rep(i, k - 1) if (P[i] + 1 < P[i + 1]){
        P[i]++;
        rep(j, i) P[j] = j;
        return true;
    }
    if (P[k - 1] < N - 1){
        P[k - 1]++;
        rep(i, k - 1) P[i] = i;
        return true;
    }
    return false;
}

// 総和が sm(P), 長さが len(P) の分割 小さい順
bool next_partition_function(vi& P){
    if (len(P) == 1) return false;
    int sm = P.back();
    for (int i = len(P) - 2; i >= 0; i--){
        if ((P[i] + 1) * (len(P) - 1 - i) < sm){
            P[i]++;
            srep(j, i + 1, len(P)) P[j] = P[i];
            sm -= P[i] * (len(P) - 1 - i);
            sm--;
            P.back() += sm;
            return true;
        }else sm += P[i];
    }
    return false;
}
