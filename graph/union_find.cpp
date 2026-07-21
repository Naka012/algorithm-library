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
