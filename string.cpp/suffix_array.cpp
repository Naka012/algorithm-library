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
const ld pi = acos(-1.0);
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
// const ll mod = 1000000007;
const ll mod = 998244353;
inline bool inside(ll y, ll x, ll H, ll W) {return 0 <= (y) and (y) < (H) and 0 <= (x) and (x) < (W); }
 
#define debug(var)  do{std::cout << #var << " : \n";view(var);}while(0)
template<typename T> void view(T e){cout << e << endl;}
template<typename T> void view(const vc<T>& v){for(const auto& e : v){ cout << e << " "; } cout << endl;}
template<typename T> void view(const vv<T>& vv){ for(const auto& v : vv){ view(v); } }

struct SuffixArray {
    string S;
    vi arr;
    SuffixArray(string &s) : S(s){
        arr.resize(len(S) + 1);
        vi rank(len(S) + 1), tmp(len(S) + 1);
        rep(i, len(S) + 1){
            arr[i] = i;
            if (i < len(S)) rank[i] = S[i];
            else rank[i] = -1;
        }
        for (int k = 1; k <= len(S); k *= 2){
            auto f = [&](auto i, auto j){
                if (rank[i] != rank[j]) return rank[i] < rank[j];
                int ni = -1, nj = -1;
                if (i + k <= len(S)) ni = rank[i + k];
                if (j + k <= len(S)) nj = rank[j + k];
                return ni < nj;
            };
            sort(all(arr), f);
            tmp[arr[0]] = 0;
            srep(i, 1, len(S) + 1){
                tmp[arr[i]] = tmp[arr[i - 1]] + f(arr[i - 1], arr[i]);
            }
            swap(rank, tmp);
        }
    }

    int operator[](int i)const{return arr[i];}

    int lower_bound(string &t){
        int top = len(S) + 1, bottom = -1;
        while (top - bottom > 1){
            int mid = (top + bottom) / 2;
            if (S.compare(arr[mid], len(t), t) >= 0) top = mid;
            else bottom = mid;
        }
        return top;
    }

    int upper_bound(string &t){
        int top = len(S) + 1, bottom = -1;
        while (top - bottom > 1){
            int mid = (top + bottom) / 2;
            if (S.compare(arr[mid], len(t), t) <= 0) bottom = mid;
            else top = mid;
        }
        return top;
    }
};
