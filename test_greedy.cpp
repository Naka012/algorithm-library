// (⁠◕⁠ᴗ⁠◕⁠✿⁠)

#include <bits/stdc++.h>
#define rep(i, n) for (ll i = 0; i < (n); i++)
using namespace std;
using ll = long long;

struct UnionFind {
    public : 
        UnionFind(int n) : _n(n){
            root = vector<int>(_n, -1);
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

        vector<vector<int>> groups(){
            vector<int> leader_buf(_n), group_size(_n);
            for (int i = 0; i < _n; i++) {
                leader_buf[i] = find(i);
                group_size[leader_buf[i]]++;
            }
            vector<vector<int>> result(_n);
            for (int i = 0; i < _n; i++) {
                result[i].reserve(group_size[i]);
            }
            for (int i = 0; i < _n; i++) {
                result[leader_buf[i]].push_back(i);
            }
            result.erase(
                remove_if(result.begin(), result.end(), [&](const vector<int>& v) { return v.empty(); }), result.end());
            return result;
        }
    private :
        int _n;
        vector<int> root;
};

struct tests{
    unsigned int randxor(){
        static unsigned int x = 123456789, y = 362436069, z = 521288629, w = 88675123;
        unsigned int t;
        t = (x ^ (x << 11)); x = y; y = z; z = w; return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }
    int randint(int a, int b) {return(a + randxor() % (b - a));}

    vector<int> randv(int N, int l, int r){
        vector<int> ret(N); rep(i, N) ret[i] = randint(l, r);
        return ret;
    }

    vector<int> randp(int N){
        vector<int> P(N); rep(i, N) P[i] = i + 1;
        rep(i, N * N){
            int x = randint(0, N), y = randint(0, N);
            swap(P[x], P[y]);
        }
        return P;
    }

    vector<vector<int>> randtree(int N){
        UnionFind uf(N);
        vector<vector<int>> g(N);
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

    vector<vector<int>> randg(int N, int M){
        set<pair<int, int>> edges;
        vector<vector<int>> g(N);
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
