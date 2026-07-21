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
dijkstra
O(|E|log |V|)

Args:
    s (int) : start
    N (int) : |V|
    g (graph)

Returns:
    dist (vl) : dist[i] := s to i 's min cost
    bef (vi) : bef[i] := path's before vertic

restore_path
O(|path|)

Args:
    start (int)
    goal (int)
    bef (vi) : dijkstra's return

Returns:
    path (vi) : path's ordered vertics numbers
*/

tuple<vl, vi> dijkstra(int s, int N, vv<pair<int, ll>> &g){
    using P = pair<ll, int>;
    vl dist(N, INF);
    vi bef(N);
    priority_queue<P, vc<P>, greater<P>> q;
    dist[s] = 0;
    q.emplace(make_pair(0, s));
    while (!q.empty()){
        P tmp = q.top();q.pop();
        ll c = tmp.first; int now = tmp.second;
        if (dist[now] < c) continue;
        for (auto&& [nxt, nc]: g[now]){
            if (dist[nxt] > dist[now] + nc){
                dist[nxt] = dist[now] + nc;
                bef[nxt] = now;
                q.emplace(make_pair(dist[nxt], nxt));
            }
        }
    }
    return {dist, bef};
}


vi restore_path_dj(int start, int goal, vi &bef){
    vi path;
    int now = goal;
    while (now != start){
        path.push_back(now);
        now = bef[now];
    }
    path.push_back(start);
    reverse(all(path));
    return path;
}


tuple<vl, vi> dijkstra(int s, int N, vv<pair<int, ll>> &g){
    using P = pair<ll, int>;
    vl dist(N, INF);
    vi bef(N);
    priority_queue<P, vc<P>, greater<P>> q;
    dist[s] = 0;
    q.push({0, s});
    while (!q.empty()){
        auto [c, now] = q.top();q.pop();
        if (dist[now] < c) continue;
        for (auto&& [nxt, nc]: g[now]) if (dist[nxt] > c + nc){
            dist[nxt] = c + nc;
            bef[nxt] = now;
            q.push({dist[nxt], nxt}); 
        }
    }
    return {dist, bef};
}
