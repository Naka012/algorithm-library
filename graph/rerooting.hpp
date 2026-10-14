// https://github.com/Naka012/algorithm-library/blob/main/graph/rerooting.hpp

/*
merge -> merge children
f1 -> (already merged -> parent can merge)
f2 -> to ans
*/

// using S = ll;
// using T = ;

// T merge(T a, T b){}
// T f1(T a, int u, int v, S cost){}
// T f2(T a, int v){}
// T e(){}
// T leaf(int){}

template <class S,
          class T,
          T (*merge)(T, T),
          T (*f1)(T, int, int, S),
          T (*f2)(T, int),
          T (*e)(),
          T (*leaf)(int)>
struct rerooting{
    public : 
        rerooting(vector<vector<pair<int, S>>> _g) : g(_g){
            N = (int)g.size();
            acc1 = vector<T>(N, e());
            acc2 = vector<T>(N, e());
            res1 = vector<T>(N, e());
            res2 = vector<T>(N, e());
            acc_bef = vector<vector<T>>(N, {e()});
            acc_aft = vector<vector<T>>(N, {e()});
        }

        void dfs0(int v, int last = -1){
            vector<T> buildup;
            int cnt = 0;
            for (auto [u, c] : g[v]) if (u != last){
                cnt++;
                dfs0(u, v);
                res1[u] = f1(acc1[u], u, v, c);
                acc1[v] = merge(acc1[v], res1[u]);
                buildup.push_back(res1[u]);
            }
            if (cnt == 0) acc1[v] = leaf(v);
            for (int i = 0; i < (int)buildup.size(); i++) acc_bef[v].push_back(merge(acc_bef[v].back(), buildup[i]));
            for (int i = (int)buildup.size() - 1; i >= 0; i--) acc_aft[v].push_back(merge(acc_aft[v].back(), buildup[i]));
        }

        void dfs1(int v, int last = -1){
            int w = 0;
            for (auto [u, c] : g[v]) if (u != last){
                acc2[u] = merge(merge(acc_bef[v][w], acc_aft[v][(int)acc_aft[v].size() - w - 2]), res2[v]);
                res2[u] = f1(acc2[u], v, u, c);
                dfs1(u, v);
                w++;
            }
        }

        vector<T> solve(){
            dfs0(0);
            dfs1(0);
            vector<T> ret(N);
            rep(v, N) ret[v] = f2(merge(acc1[v], res2[v]), v);
            return ret;
        }

    private : 
        int N;
        vector<vector<pair<int, S>>> g;
        vector<T> acc1, acc2, res1, res2;
        vector<vector<T>> acc_bef, acc_aft;
};
