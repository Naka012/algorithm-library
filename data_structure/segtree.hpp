// https://github.com/Naka012/algorithm-library/blob/main/data_structure/segtree.hpp

/*
segtree<ll , op, e> st(N);

*/

template<class T, T (*op)(T, T), T (*e)()> struct segtree{
    public : 
        segtree(int n) : _n(n){
            depth = 0;
            while ((1 << depth) < _n) depth++;
            size = 1 << depth;
            tree = vector<T>(2 * size, e());
        }

        void set(int p, T x){
            assert (0 <= p && p < _n);
            p += size;
            tree[p] = x;
            for (int i = 0; i < depth; i++){
                p >>= 1;
                tree[p] = op(tree[2 * p], tree[2 * p + 1]);
            }
            return;
        }

        T get(int p){
            assert(0 <= p && p < _n);
            return tree[p + size];
        }

        T prod(int l, int r){
            assert (0 <= l && l <= r && r <= _n);
            if (l == r) return e();
            T nl = e(), nr = e();
            l += size;
            r += size;
            while(l < r){
                if (l & 1) nl = op(nl, tree[l++]);
                // if (r & 1) nr = op(nr, tree[--r]);
                if (r & 1) nr = op(tree[--r], nr);
                l >>= 1;
                r >>= 1;
            }
            return op(nl, nr);
        }
    
    private : 
        int _n, depth, size;
        vector<T> tree;
};
