template<class T, T (*op)(T, T), T (*e)()> struct twoD_segtree{
    public : 
        twoD_segtree(int h, int w) : _h(h){
            _w = w;
            depth = 0;
            while ((1 << depth) < _h) depth++;
            size = 1 << depth;
            inner_depth = 0;
            while ((1 << inner_depth) < _w) inner_depth++;
            inner_size = 1 << inner_depth;
            tree = vector<vector<T>>(2 * size, vector<T>(2 * inner_size, e()));
        }

        void inner_set(int nw, int p, T &x){
            assert (0 <= p && p < _w);
            p += inner_size;
            tree[nw][p] = x;
            for (int i = 0; i < inner_depth; i++){
                p >>= 1;
                tree[nw][p] = op(tree[nw][2 * p], tree[nw][2 * p + 1]);
            }
            return;
        }

        T inner_prod(int &nw, int l, int r){
            assert (0 <= l && l < r && r <= _w);
            T nl = e(), nr = e();
            l += inner_size;
            r += inner_size;
            while(l < r){
                if (l & 1) nl = op(nl, tree[nw][l++]);
                if (r & 1) nr = op(nr, tree[nw][--r]);
                l >>= 1;
                r >>= 1;
            }
            return op(nl, nr);
        }

        void set(int hp, int wp, T x){
            assert (0 <= hp && hp < _h && 0 <= wp && wp < _w);
            hp += size;
            inner_set(hp, wp, x);
            for (int i = 0; i < depth; i++){
                hp >>= 1;
                ll x = op(tree[2 * hp][wp + inner_size], tree[2 * hp + 1][wp + inner_size]);
                inner_set(hp, wp, x);
            }
            return;
        }

        T get(int hp, int wp){
            assert (0 <= hp && hp < _h && 0 <= wp && wp < _w);
            return tree[hp + size][wp + inner_size];
        }

        T prod(int hl, int hr, int wl, int wr){
            assert (0 <= hl && hl < hr && hr <= _h);
            T nl = e(), nr = e();
            hl += size;
            hr += size;
            while(hl < hr){
                if (hl & 1){
                    nl = op(nl, inner_prod(hl, wl, wr));
                    hl++;
                }
                if (hr & 1){
                    hr--;
                    nr = op(nr, inner_prod(hr, wl, wr));
                }
                hl >>= 1;
                hr >>= 1;
            }
            return op(nl, nr);
        }

    private : 
        int _h, _w, depth, size, inner_depth, inner_size;
        vector<vector<T>> tree;
};
