template<class T, T (*op)(T, T), T (*e)()> struct DynamicSegtree{
    public : 
        DynamicSegtree(ll n) : _n(n){
            depth = 0;
            while ((1ll << depth) < _n) depth++;
            size = 1ll << depth;
        }

        void set(ll p, T x){
            assert (0 <= p && p < _n);
            p += size;
            tree[p] = x;
            for (ll i = 0; i < depth; i++){
                p >>= 1;
                tree[p] = op(tree[2 * p], tree[2 * p + 1]);
            }
            return;
        }

        T get(ll p){
            assert(0 <= p && p < _n);
            return tree[p + size];
        }

        T prod(ll l, ll r){
            assert (0 <= l && l <= r && r <= _n);
            if (l == r) return e();
            T nl = e(), nr = e();
            l += size;
            r += size;
            while(l < r){
                if (l & 1){
                    nl = op(nl, tree[l]);
                    l++;
                }
                if (r & 1){
                    r--;
                    nr = op(nr, tree[r]);
                }
                l >>= 1;
                r >>= 1;
            }
            return op(nl, nr);
        }
        T all_prod(){return tree[1];}
    private : 
        ll _n, depth, size;
        unordered_map<ll, T> tree;
};
