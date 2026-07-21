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
const double pi = 3.141592653589793;
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
// const ll mod = 1000000007;
const ll mod = 998244353;

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

ll BsGs(ll x, ll y, ll md){
    unordered_map<ll, ll> babys;
    ll nw = 1, sq = sqrt(md) + 1;
    for (ll i = 0; i < sq; i++){
        if (!babys.count(nw)) babys[nw] = i;
        nw = nw * x % md;
    }
    ll giant = y, inv = pow_mod(pow_mod(x, md - 2, md), sq, md);
    for (int i = 0; i <= sq; i ++){
        if (babys.count(giant)) return babys[giant] + i * sq;
        giant = giant * inv % md;
    }
    return -1;
}

