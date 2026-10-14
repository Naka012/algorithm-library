// https://github.com/Naka012/algorithm-library/blob/main/data_structure/dual_segtree.hpp

template<class T, T (*op)(T, T), T (*e)()> struct dual_segtree{
    public : 
        dual_segtree(int n) : _n(n){
            depth = 0;
            while ((1 << depth) < _n) depth++;
            size = 1 << depth;
            tree = vector<T>(2 * size, e());
        }

        void set(int l, int r, T x){
            assert (0 <= l && l <= r && r <= _n);
            if (l == r) return;
            l += size;
            r += size;
            while(l < r){
                if (l & 1){
                    tree[l] = op(x, tree[l]);
                    l++;
                }
                if (r & 1){
                    r--;
                    tree[r] = op(x, tree[r]);
                }
                l >>= 1;
                r >>= 1;
            }
            return;
        }

        T get(int p){
            assert(0 <= p && p <= _n);
            p += size;
            T ret = e();
            while (p){
                ret = op(ret, tree[p]);
                p >>= 1;
            }
            return ret;
        }

    private : 
        int _n, depth, size;
        vector<T> tree;
};
