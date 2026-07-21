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
topological sort
O(|V| + |E|)

Args:
    N (int) : graph size
    g (vvi) : g[i] := edge (i to j)
    enterdeg (vi) : enterdeg[i] := enter degree of i

Returns:
    bool : false -> exist sycle
           true -> not ""
    vi : result
*/

tuple<bool, vi> topological_sort(int &N, vvi &g, vi &enterdeg){
    priority_queue<int, vi, greater<int>> q;
    for (int i = 0; i < N; i++){
        if (enterdeg[i] == 0) q.push(i);
    }
    vi ret;
    while (!q.empty()){
        int now = q.top(); q.pop();
        ret.push_back(now);
        for (auto nxt : g[now]){
            enterdeg[nxt] -= 1;
            if (enterdeg[nxt] == 0) q.push(nxt);
        }
    }
    if (len(ret) == N) return {true, ret};
    return {false, {}};
}
