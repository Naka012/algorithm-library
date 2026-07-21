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

struct bitbase {
    public :
        bitbase(int _k) : k(_k) {
            base = vl(k + 1, 0);
        }

        void add(ll x){
            for (int i = k; i >= 0; i--) if (x >> i & 1) x ^= base[i];
            if (x == 0) return;
            for (int i = k; i >= 0; i--) if (x >> i & 1){
                for (auto& b : base) if (b >> i & 1) b ^= x;
                base[i] = x;
                return;
            }
        }

        bool in(ll x){
            for (int i = k; i >= 0; i--) if (x >> i & 1) x ^= base[i];
            return (x ? false : true);
        }

        ll get(ll id){
            id--;
            ll ret = 0;
            rep(i, k + 1) if (base[i]){
                if (id & 1) ret ^= base[i];
                id >>= 1;
            }
            return ret;
        }

        ll leader(int i){return base[i];}
    private :
        int k;
        vl base;
};