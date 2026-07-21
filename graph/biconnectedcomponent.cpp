// (◕ᴗ◕✿)

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

#define debug(var) do { cerr << #var << " :\n"; view(var); } while(0)
template<typename T>void view(const T& e) {cerr << e;}
template<typename T1, typename T2>void view(const pair<T1, T2>& p) {cerr << "{" << p.first << ", " << p.second << "}";}
template<typename T>void view(const vc<T>& v) {for (const auto& e : v) {view(e);cerr << " ";} cerr << endl;}
template<typename T>void view(const vv<T>& vv) {for (const auto& v : vv) {view(v);} cerr << endl;}
template<typename T>void view(const set<T>& s) {for (const auto& e : s) {view(e);cerr << " ";} cerr << endl;}
template<typename T>void view(const multiset<T>& s) {for (const auto& e : s) {view(e);cerr << " ";} cerr << endl;}
template<typename T>void view(const unordered_set<T>& s) {for (const auto& e : s) {view(e);cerr << " ";} cerr << endl;}
template<typename T1, typename T2>void view(const map<T1, T2>& mp){for (const auto& e : mp) {view(e);cerr << " ";} cerr << endl;}

struct BiconnectedComponent {
    vi ord, low;
    vi used;
    vvi g;
    vv<pair<int, int>> bc;
    vc<pair<int, int>> tmp;
    int n, k = 0;
    BiconnectedComponent(const vvi &g) : g(g) {
        n = g.size();
        ord.resize(n, -1);
        low.resize(n, -1);
        used.resize(n, 0);
        dfs(0, -1);
    }
    void dfs(int u, int prev) {
        used[u] = true;
        ord[u] = k++;
        low[u] = ord[u];
        int cnt = 0;
        for (auto v : g[u]) if (v != prev) {
            if (ord[v] < ord[u]) { 
                tmp.emplace_back(minmax(u, v));
            }
            if (!used[v]){
                cnt++;
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] >= ord[u]) {
                    bc.push_back({});
                    while (true) {
                        auto e = tmp.back();
                        bc.back().emplace_back(e);
                        tmp.pop_back();
                        if (min(u, v) == e.first && max(u, v) == e.second) {
                            break;
                        }
                    }
                }
            }else{
                low[u] = min(low[u], ord[v]);
            }
        }
    }
};
