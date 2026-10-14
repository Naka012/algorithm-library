// https://github.com/Naka012/algorithm-library/blob/main/data_structure/fenwick_tree.hpp

template<class T> struct fenwick_tree {
    public : 
        fenwick_tree(int n) : _n(n) {
            tree = vector<T>(_n, 0);
        }
        
        void add(int p, T x){
            assert(0 <= p && p < _n);
            p++;
            while (p <= _n) {
                tree[p - 1] += x;
                p += p & -p;
            }
        }
        
        T sum_(int p){
            T ret = 0;
            while (p > 0){
                ret += tree[p - 1];
                p -= p & -p;
            }
            return ret;
        }
        
        T sum(int l, int r){
            assert(0 <= l && l < r && r <= _n);
            return sum_(r) - sum_(l);
        }
    private : 
        int _n;
        vector<T> tree;
};
