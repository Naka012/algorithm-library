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

ll primitive_root(ll &md){
    if (md == 2) return 1;
    if (md == 167772161) return 3;
    if (md == 469762049) return 3;
    if (md == 754974721) return 11;
    if (md == 998244353) return 3;
    if (md == 1228668929) return 14;
    vl fac;
    ll i = 1;
    while (i * i < md){
        if ((md - 1) % i == 0){
            if (i != 1) fac.push_back(i);
            if (i != (md - 1) / i && (md - 1) / i != 1) fac.push_back((md - 1) / i);
        }
        i++;
    }
    ll now = 2;
    while (true){
        bool flag = true;
        for (auto x : fac){
            if (pow_mod(now, (md - 1) / x, md) == 1){
                flag = false;
                break;
            }
        }
        if (flag) return now;
        now++;
    }
}

void fft(vl &a, ll w, ll &md) {
    int n = len(a);
    int h = 0;
    while(1 << h < n) h++;
    for (int i = 0; i < n; i++) {
        int j = 0;
        for (int k = 0; k < h; k++) j |= (i >> k & 1) << (h - 1 - k);
        if (i < j) swap(a[i], a[j]);
    }

    vl ws;
    for (int b = 1; b < n; b *= 2){
        ws.push_back(w);
        w = w * w;
        w %= md;
    }
    reverse(all(ws));
    ll b = 1;
    for (auto nw : ws) {
        ll z = 1;
        for (int j = 0; j < b; j++) {
            for (int k = 0; k < n; k += b * 2) {
                ll s = a[j + k];
                ll t = a[j + k + b] * z % md;
                a[j + k] = (s + t) % md;
                a[j + k + b] = (s - t + md) % md;
            }
            z *= nw;
            z %= md;
        }
        b *= 2;
    }
}

vl convolution(vl &A, vl &B, ll md){
    ll lA = len(A), lB = len(B), d = lA + lB - 1, prime = primitive_root(md);
    ll length = 0;
    while (1 << length < d) length++;
    length = 1 << length;
    A.resize(length, 0);
    B.resize(length, 0);
    ll W = pow_mod(prime, (md - 1) / length, md), inv_W = pow_mod(W, md - 2, md), inv_N = pow_mod(length, md - 2, md);
    fft(A, W, md);
    fft(B, W, md);
    vl fAB(length); for (int i = 0; i < length; i++) fAB[i] = A[i] * B[i] % md;
    fft(fAB, inv_W, md);
    vl ret(length); for (int i = 0; i < length; i++) ret[i] = fAB[i] * inv_N % md;
    ret.resize(d);
    return ret;
}
