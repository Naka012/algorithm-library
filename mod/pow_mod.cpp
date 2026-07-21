#include <bits/stdc++.h>
// #include <atcoder/all>
// using namespace atcoder;
// using mint = modint1000000007;
// using mint = modint998244353;
// using vmint = vc<mint>;using vvmint = vc<vmint>;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define srep(i, s, n) for (int i = s; i < n; i++)
#define drep(i, n) for (int i = n; i >= 0; i--)
#define dsrep(i, s, n) for (int i = s; i >= n; i--)
#define len(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define YES(n) cout << ((n) ? "YES" : "NO" ) << endl
#define Yes(n) cout << ((n) ? "Yes" : "No" ) << endl
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



ll pow_mod(ll a, ll d, ll m){
    ll ret = 1;
    while (d > 0){
        if (d & 1){
            ret *= a;
            ret %= m;
        }
        a = a * a % m;
        d >>= 1;
    }
    return ret;
}
