// (⁠◕⁠ᴗ⁠◕⁠✿⁠)

#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
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

const ull MOD = (1ull << 61) - 1;
const ull base = 20200213;
struct hint{
    ull val;
    hint() {};
    hint(ull v) {
        if (v < MOD) val = v;
        else{
            v %= MOD;
            val = v;
        }
    }

    friend hint operator+(const hint& u, const hint& v){
        auto tmp = u.val + v.val;
        if (tmp >= MOD) tmp -= MOD;
        return tmp;
    }

    friend hint operator-(const hint& u, const hint& v){
        if (u.val < v.val) return u.val + MOD - v.val;
        return u.val - v.val;
        
    }

    friend hint operator*(const hint& u, const hint& v){
        auto ua = u.val >> 31, ub = u.val & ((1ull << 31) - 1), va = v.val >> 31, vb = v.val & ((1ull << 31) - 1);
        auto mid = ua * vb + va * ub;
        auto mida = mid >> 30, midb = mid & ((1ull << 30) - 1);
        auto ret = ua * va * 2ull + mida + (midb << 31) + ub * vb;
        ret = (ret >> 61) + (ret & ((1ull << 61) - 1));
        if (ret >= MOD) ret -= MOD;
        return ret;
    }

    hint pow(ull n){
        hint a = *this, ret = 1;
        while (n > 0){
            if (n & 1) ret = ret * a;
            a = a * a;
            n >>= 1;
        }
        return ret;
    }
    friend bool operator==(const hint& u, const hint& v){return u.val == v.val;}
    friend bool operator!=(const hint& u, const hint& v){return u.val != v.val;}
};
