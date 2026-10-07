template<class T> struct raq_fenwick_tree {
    public : 
        raq_fenwick_tree(int n) : _n(n) {
            tree0 = vector<T>(_n, 0);
            tree1 = vector<T>(_n, 0);
        }
        
        void add_(int p, T x, vector<T> &tree){
            assert(0 <= p && p < _n);
            p++;
            while (p <= _n) {
                tree[p - 1] += x;
                p += p & -p;
            }
        }

        void add(int l, int r, T x){
            assert(0 <= l && l < r && r <= _n);
            add_(l, -x * (l - 1), tree0);
            add_(r + 1, x * r, tree0);
            add_(l, x, tree1);
            add_(r + 1, -x, tree1);
        }
        
        T sum__(int p, vector<T> &tree){
            T ret = 0;
            while (p > 0){
                ret += tree[p - 1];
                p -= p & -p;
            }
            return ret;
        }
        
        T sum_(int p){
            return sum__(p, tree0) + sum__(p, tree1) * p;
        }

        T sum(int l, int r){
            assert(0 <= l && l < r && r <= _n);
            return sum_(r) - sum_(l);
        }
    private : 
        int _n;
        vector<T> tree0, tree1;
};
