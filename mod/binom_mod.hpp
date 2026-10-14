// https://github.com/Naka012/algorithm-library/blob/main/mod/binom_mod.hpp

template<int MOD> struct modint {
    static constexpr int Mod = MOD;
    int val;
    using mint = modint;
    modint() {};
    modint(ll v) {
        if (0 <= v && v < Mod) val = v;
        else{
            v %= Mod;
            if (v < 0) v += Mod;
            val = v;
        }
    }
    mint operator++(int){
        val++;
        if (val == Mod) val = 0;
        return *this;
    }
    mint operator--(int){
        if (val == 0) val = Mod;
        val--;
        return *this;
    }
    mint& operator+=(const mint& v){
        val += v.val;
        if (val >= Mod) val -= Mod;
        return *this;
    }
    mint& operator-=(const mint& v){
        val -= v.val;
        if (val < 0) val += Mod;
        return *this;
    }
    mint& operator*=(const mint& v){
        val = (int)(1ll * val * v.val % Mod);
        return *this;
    }
    modint inverse() const {
        int a = val, b = Mod, u = 1, v = 0, t;
        while (b > 0) {
        t = a / b;
        swap(a -= t * b, b), swap(u -= t * v, v);
        }
        return modint(u);
    }
    mint pow(ll n) const {
        mint a = *this, ret = 1;
        while (n > 0){
            if (n & 1) ret *= a;
            a *= a;
            n >>= 1;
        }
        return ret;
    }
    mint& operator>>=(ll k){
        *this *= mint(2).pow(k).pow(Mod - 2);
        return *this;
    }
    mint& operator<<=(ll k){
        *this *= mint(2).pow(k);
        return *this;
}
    mint operator/=(const mint& v){
        *this *= v.inverse();
        return *this;
    }
    mint operator-() const { return mint(-val);}
    friend mint operator+(const mint& u, const mint& v){return mint(u) += v;}
    friend mint operator-(const mint& u, const mint& v){return mint(u) -= v;}
    friend mint operator*(const mint& u, const mint& v){return mint(u) *= v;}
    friend mint operator/(const mint& u, const mint& v){return mint(u) /= v;}
    friend bool operator==(const mint& u, const mint& v){return u.val == v.val;}
    friend bool operator!=(const mint& u, const mint& v){return u.val != v.val;}
    friend bool operator>(const mint& u, const mint& v){return u.val > v.val;}
    friend bool operator<(const mint& u, const mint& v){return u.val < v.val;}
    friend mint operator>>(mint& u, const ll k){return u >>= k;}
    friend mint operator<<(mint& u, const ll k){return u <<= k;}
    friend ostream& operator<<(ostream& stream, const mint& v){
        stream << v.val;
        return stream;
    }
};

using mint = modint<998244353>;

struct Binoms {
    public : 
        Binoms(int n){
            fact = vector<mint>(1, 1);
            inv_fact = vector<mint>(1, 1);
            update(n);
        };

        void update(int n){
            if (sz >= n) return;
            fact.resize(n + 1, 1);
            inv_fact.resize(n + 1, 1);
            for (int i = sz; i < n; i++) fact[i + 1] = fact[i] * (i + 1);
            inv_fact[n] = 1 / fact[n];
            for (int i = n - 1; i >= sz + 1; i--) inv_fact[i] = inv_fact[i + 1] * (i + 1);
            sz = n;
            return;
        }

        mint C(int n, int k){
            if (n < k || k < 0) return 0;
            if (sz < n) update(n);
            return fact[n] * inv_fact[n - k] * inv_fact[k];
        }

        mint fac(int n){
            if (sz < n) update(n);
            return fact[n];
        }

        mint invfac(int n){
            if (sz < n) update(n);
            return inv_fact[n];
        }

    private :
        int sz = 0;
        vector<mint> fact, inv_fact;
};
