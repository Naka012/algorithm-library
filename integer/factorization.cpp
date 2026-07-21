#include <bits/stdc++.h>
#define len(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
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

struct phash{
    inline size_t operator()(const pair<int,int> & p) const{
        const auto h1 = hash<int>()(p.first);
        const auto h2 = hash<int>()(p.second);
        return h1 ^ (h2 << 1);
    }
};

/*
素因数分解
O(sqrt N)

Args:
    N (ll): 元の数

Return:
    factors (vc<pair<int, int>>): pair(i, j) := i が j 個含まれる

*/

vc<pair<ll, ll>> factorization(ll &N){
    vc<pair<ll, ll>> factors;
    ll tmp = N;
    for (ll i = 2; i * i <= N + 1; i++){
        if (tmp % i == 0){
            int cnt = 0;
            while (tmp % i == 0){
                tmp /= i;
                cnt += 1;
            }
            factors.push_back({i, cnt});
        }
    }
    if (tmp != 1){
        factors.push_back({tmp, 1});
    }
    if (len(factors) == 0){
        factors.push_back({N, 1});
    }
    return factors;
}
