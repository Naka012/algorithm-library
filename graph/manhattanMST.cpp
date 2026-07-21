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
頂点が平面上にあり、マンハッタン距離を辺の重みにしたときの
最小全域木 の候補辺列挙

O(|V| log |V|)
*/

vc<tuple<ll, int, int>> manhattanMST(vc<pair<ll, ll>> &points){
    int N = len(points);
    vc<tuple<ll, int, int>> ret;
    vi idx(N);
    iota(all(idx), 0);
    for (int s = 0; s < 2; s++) {
        for (int t = 0; t < 2; t++) {
            sort(all(idx), [&](int i, int j) { 
                return points[i].first + points[i].second < points[j].first + points[j].second;
                }
            );
            map<ll, int> sweep;

            for (int i : idx) {
                for (auto it = sweep.lower_bound(-points[i].second); it != sweep.end(); it = sweep.erase(it)) {
                    int j = it->second;
                    if (points[i].first - points[j].first < points[i].second - points[j].second) break;
                    ret.push_back({abs(points[i].first - points[j].first) + abs(points[i].second - points[j].second), i, j});
                }
                sweep[-points[i].second] = i;
            }
            for (auto &p : points) swap(p.first, p.second);
        }
        for (auto &p : points) p.first = -p.first;
    }

    sort(all(ret));
    return ret;
}
