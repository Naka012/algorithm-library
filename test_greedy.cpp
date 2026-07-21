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
const ld pi = 3.141592653589793;
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
// const ll mod = 1000000007;
const ll mod = 998244353;
inline bool inside(ll y, ll x, ll H, ll W) {return 0 <= (y) and (y) < (H) and 0 <= (x) and (x) < (W); }

#define debug(var)  do{std::cout << #var << " : \n";view(var);}while(0)
template<typename T> void view(T e){cout << e << endl;}
template<typename T> void view(const vc<T>& v){for(const auto& e : v){ cout << e << " "; } cout << endl;}
template<typename T> void view(const vv<T>& vv){ for(const auto& v : vv){ view(v); } }

struct UnionFind {
    public : 
        UnionFind(int n) : _n(n){
            root = vi(_n, -1);
        }

        int find(int x){
            if (root[x] < 0) return x;
            return root[x] = find(root[x]);
        }

        void unite(int a, int b){
            a = find(a); b = find(b);
            if (a == b) return;
            if (size(a) < size(b)) swap(a, b);
            root[a] += root[b];
            root[b] = a;
        }
        
        bool same(int a, int b){
            return find(a) == find(b);
        }

        int size(int a){
            return -root[find(a)];
        }

        int group(){
            int ret = 0;
            for (int i = 0; i < _n; i++) if (root[i] < 0) ret++;
            return ret;
        }

        vvi groups(){
            vi leader_buf(_n), group_size(_n);
            for (int i = 0; i < _n; i++) {
                leader_buf[i] = find(i);
                group_size[leader_buf[i]]++;
            }
            vvi result(_n);
            for (int i = 0; i < _n; i++) {
                result[i].reserve(group_size[i]);
            }
            for (int i = 0; i < _n; i++) {
                result[leader_buf[i]].push_back(i);
            }
            result.erase(
                remove_if(result.begin(), result.end(), [&](const vi& v) { return v.empty(); }), result.end());
            return result;
        }
    private :
        int _n;
        vi root;
};

struct tests{
    unsigned int randxor(){
        static unsigned int x = 123456789, y = 362436069, z = 521288629, w = 88675123;
        unsigned int t;
        t = (x ^ (x << 11)); x = y; y = z; z = w; return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }
    int randint(int a, int b) {return(a + randxor() % (b - a));}

    vi randv(int N, int l, int r){
        vi ret(N); rep(i, N) ret[i] = randint(l, r);
        return ret;
    }

    vi randp(int N){
        vi P(N); rep(i, N) P[i] = i + 1;
        rep(i, N * N){
            int x = randint(0, N), y = randint(0, N);
            swap(P[x], P[y]);
        }
        return P;
    }

    vvi randtree(int N){
        UnionFind uf(N);
        vvi g(N);
        int edge = 0;
        while (edge < N - 1){
            int u = randint(0, N), v = randint(0, N);
            if (!uf.same(u, v)){
                uf.unite(u, v);
                g[u].push_back(v);
                g[v].push_back(u);
                edge++;
            }
        }
        return g;
    }

    vvi randg(int N, int M){
        set<pair<int, int>> edges;
        vvi g(N);
        rep(i, M){
            int u = randint(0, N), v = randint(0, N);
            while (true){
                if (!edges.count({min(u, v), max(u, v)})) break;
                u = randint(0, N);
                v = randint(0, N);
            }
            edges.insert({min(u, v), max(u, v)});
            g[u].push_back(v);
            g[v].push_back(u);
        }
        return g;
    }
};

void greedy(){
}

int main(){
    rep(i, 10){
    }
    return 0;
}