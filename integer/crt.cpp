// (⁠◕⁠ᴗ⁠◕⁠✿⁠)
 
#include <bits/stdc++.h>
#define rep(i, n) for (ll i = 0; i < (n); i++)
#define srep(i, s, n) for (ll i = s; i < (n); i++)
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
const ll mod = 1000000007;
// const ll mod = 998244353;

/*
return min(x) s.t. x = a (mod1) && x = b (mod2)
*/
ll extra_gcd(ll a, ll b, ll &x, ll &y){
    if (b == 0){
        x = 1;
        y = 0;
        return a;
    }
    ll ret = extra_gcd(b, a % b, y, x);
    y -= a / b * x;

    return ret;
}

ll crt(ll mod1, ll a, ll mod2, ll b){
    if (mod1 < mod2){
        swap(mod1, mod2);
        swap(a, b);
    }
    if (mod1 % mod2 == 0 && a % mod2 != b) return -1;
    ll x, y, g;
    g = extra_gcd(mod1, mod2, x, y);
    x %= mod2;
    if (x < 0) x += mod2;
    if ((b - a) % g) return -1;
    ll m = mod2 / g, l = mod1 * m, tmp = (b - a) / g % m * x % m;
    ll ret = tmp * mod1 + a;
    if (ret < 0) ret += l;
    return ret;
}
