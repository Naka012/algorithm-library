struct bitbase {
    public :
        bitbase(int _k) : k(_k) {
            base = vector<ll>(k + 1, 0);
        }

        void add(ll x){
            for (int i = k; i >= 0; i--) if (x >> i & 1) x ^= base[i];
            if (x == 0) return;
            for (int i = k; i >= 0; i--) if (x >> i & 1){
                for (auto& b : base) if (b >> i & 1) b ^= x;
                base[i] = x;
                return;
            }
        }

        bool in(ll x){
            for (int i = k; i >= 0; i--) if (x >> i & 1) x ^= base[i];
            return (x ? false : true);
        }

        ll get(ll id){
            id--;
            ll ret = 0;
            rep(i, k + 1) if (base[i]){
                if (id & 1) ret ^= base[i];
                id >>= 1;
            }
            return ret;
        }

        ll leader(int i){return base[i];}
    private :
        int k;
        vector<ll> base;
};
