// https://github.com/Naka012/algorithm-library/blob/main/formal_power_series/differential_equation.hpp

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
    friend ostream& operator<<(ostream& stream, mint& v){
        stream << v.val;
        return stream;
    }
};

using mint = modint<998244353>;

// return f s.t. a * f' + b * f = 0
vector<mint> differential_equation(vector<mint> a, vector<mint> b){
    assert(a[0] == 1);
    int N = (int)a.size();
    vector<pair<int, mint>> na, nb;
    rep(i, N){
        if (a[i] != 0) na.push_back({i, a[i]});
        if (b[i] != 0) nb.push_back({i, b[i]});
    }
    vector<mint> f(N, 0);
    f[0] = 1;
    rep(i, N - 1){
        for (auto [j, aj] : na){
            if (j > i + 1) break;
            if (j) f[i + 1] -= aj * (i + 1 - j) * f[i + 1 - j];
        }
        for (auto [j, bj] : nb){
            if (j > i) break;
            f[i + 1] -= bj * f[i - j];
        }
        f[i + 1] /= i + 1;
    }
    return f;
}
