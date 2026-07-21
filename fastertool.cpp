// (⁠◕⁠ᴗ⁠◕⁠✿⁠)

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
using vi = vc<int>;using vvi = vv<int>; using vvvi = vv<vi>;
using ll = long long;using vl = vc<ll>;using vvl = vv<ll>; using vvvl = vv<vl>;
using ld = long double; using vld = vc<ld>; using vvld = vc<vld>; using vvvld = vc<vvld>;
using uint = unsigned int;
using ull = unsigned long long;
const double pi = 3.141592653589793;
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
// const int mod = 1000000007;
const int mod = 998244353;
inline bool inside(long long y, long long x, long long H, long long W) {return 0 <= y and y < H and 0 <= x and x < W; }



/*
pow
*/

ll pw(ll a, ll d){
    ll ret = 1;
    while (d > 0){
        if (d & 1){
            ret *= a;
        }
        a = a * a;
        d >>= 1;
    }
    return ret;
}

/*
floor
*/

ll floor(ll x, ll a){
    if (x >= 0) return x / a;
    return (x - a + 1) / a;
}

/*
grid move
*/

vi dx = {1, 0, -1, 0}, dy = {0, 1, 0, -1};
vi dx = {1, 0, -1, 0, 1, 1, -1, -1}, dy = {0, 1, 0, -1, 1, -1, 1, -1};

vc<pair<int, int>> d1 = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
vc<pair<int, int>> d2 = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

// std::random_device seed_gen;
// std::mt19937_64 engine(seed_gen());
// std::uniform_int_distribution<> dist(1, 100);

// #include <ext/pb_ds/assoc_container.hpp>
// using namespace __gnu_pbds;
// template <class T>
// using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
