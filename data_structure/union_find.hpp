// https://github.com/Naka012/algorithm-library/blob/main/data_structure/union_find.hpp

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
