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

/*
mo mo
O(???)
でもまにあうしはやい

query(l, r) := [l, r)
out(i) := answer i th query

*/

ll hilbertorder(int x, int y, ll maxn) {
  ll rx, ry, d = 0;
  for (ll s = maxn >> 1; s; s >>= 1) {
    rx = (x & s)>0, ry = (y & s)>0;
    d += s * s * ((rx * 3) ^ ry);
    if (ry) continue;
    if (rx) {
      x = maxn - 1 - x;
      y = maxn - 1 - y;
    }
    swap(x, y);
  }
  return d;
}

void mo_algo(int N, vc<pair<int, int>> &querys, auto add_l, auto add_r, auto erase_l, auto erase_r, auto out){
    int Q = len(querys);
    vi order(Q);
    iota(all(order), 0);
    ll maxn = 1;
    while (maxn < N) maxn <<= 1;
    vl eval(Q);
    for (int i = 0; i < Q; i++) eval[i] = hilbertorder(querys[i].first, querys[i].second, maxn);

    sort(all(order), [&](int i, int j) {
        return eval[i] < eval[j];
    });

    int nl = 0, nr = 0;
    for(int i : order) {
        auto& [l, r] = querys[i];
        while(nl > l) add_l(--nl);
        while(nr < r) add_r(nr++);
        while(nl < l) erase_l(nl++);
        while(nr > r) erase_r(--nr);
        out(i);
    }
    return;
}

