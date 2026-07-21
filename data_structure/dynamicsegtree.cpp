// (⁠◕⁠ᴗ⁠◕⁠✿⁠)

// #pragma GCC target("avx2")
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
const ld pi = acos(-1.0);
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
// const ll mod = 1000000007;
const ll mod = 998244353;
inline bool inside(ll y, ll x, ll H, ll W) {return 0 <= (y) and (y) < (H) and 0 <= (x) and (x) < (W); }

#define debug(var) do { cout << #var << " :\n"; view(var); } while(0)
template<typename T>void view(const T& e) {cout << e;}
template<typename T1, typename T2>void view(const pair<T1, T2>& p) {cout << "{" << p.first << ", " << p.second << "}";}
template<typename T>void view(const vc<T>& v) {for (const auto& e : v) {view(e);cout << " ";} cout << endl;}
template<typename T>void view(const vv<T>& vv) {for (const auto& v : vv) {view(v);cout << " ";} cout << endl;}
template<typename T>void view(const set<T>& s) {for (const auto& e : s) {view(e);cout << " ";} cout << endl;}
template<typename T>void view(const unordered_set<T>& s) {for (const auto& e : s) {view(e);cout << " ";} cout << endl;}
template<typename T1, typename T2>void view(const map<T1, T2>& mp){for (const auto& e : mp) {view(e);cout << " ";} cout << endl;}

template<class T, T (*op)(T, T), T (*e)()> struct DynamicSegtree{
    public : 
        DynamicSegtree(ll n) : _n(n){
            depth = 0;
            while ((1ll << depth) < _n) depth++;
            size = 1ll << depth;
        }

        void set(ll p, T x){
            assert (0 <= p && p < _n);
            p += size;
            tree[p] = x;
            for (ll i = 0; i < depth; i++){
                p >>= 1;
                tree[p] = op(tree[2 * p], tree[2 * p + 1]);
            }
            return;
        }

        T get(ll p){
            assert(0 <= p && p < _n);
            return tree[p + size];
        }

        T prod(ll l, ll r){
            assert (0 <= l && l <= r && r <= _n);
            if (l == r) return e();
            T nl = e(), nr = e();
            l += size;
            r += size;
            while(l < r){
                if (l & 1){
                    nl = op(nl, tree[l]);
                    l++;
                }
                if (r & 1){
                    r--;
                    nr = op(nr, tree[r]);
                }
                l >>= 1;
                r >>= 1;
            }
            return op(nl, nr);
        }
        T all_prod(){return tree[1];}
    private : 
        ll _n, depth, size;
        unordered_map<ll, T> tree;
};
