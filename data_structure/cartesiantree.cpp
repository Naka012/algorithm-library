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
// const ll mod = 1000000007;
const ll mod = 998244353;

template <typename T> pair<vvi, int> cartesiantree(vc<T> &a) {
    int N = (int)a.size();
    vvi g(N);
    vi p(N, -1), st;
    st.reserve(N);
    for (int i = 0; i < N; i++) {
        int prv = -1;
        while (!st.empty() && a[i] < a[st.back()]) {
            prv = st.back();
            st.pop_back();
        }
        if (prv != -1) p[prv] = i;
        if (!st.empty()) p[i] = st.back();
        st.push_back(i);
    }
    int root = -1;
    for (int i = 0; i < N; i++) {
        if (p[i] != -1)
            g[p[i]].push_back(i);
        else
            root = i;
    }
    return make_pair(g, root);
}
