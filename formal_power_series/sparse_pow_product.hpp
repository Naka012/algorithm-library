// https://github.com/Naka012/algorithm-library/blob/main/formal_power_series/sparse_pow_product.hpp
// 出典 (sparse_pow_product): https://github.com/maspypy/library/blob/8214a57a17d98155085eab33064b6115e12c85f1/poly/sparse_pow_product.hpp
// 参考 (differential_equation): https://github.com/maspypy/library/blob/8214a57a17d98155085eab33064b6115e12c85f1/poly/sparse_FODE.hpp

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
vector<mint> differential_equation(const vector<mint> &a, const vector<mint> &b){
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
            if (j) f[i + 1] -= aj * mint(i + 1 - j) * f[i + 1 - j];
        }
        for (auto [j, bj] : nb){
            if (j > i) break;
            f[i + 1] -= bj * f[i - j];
        }
        f[i + 1] /= i + 1;
    }
    return f;
}
// return f^n * g^m
vector<mint> sparse_pow_product(vector<mint>& f, vector<mint>& g, mint n, mint m) {
  int N = (int)f.size();
  assert(f[0] == 1);
  vector<pair<int, mint>> nf, ng;
  rep(i, (int)f.size()) if (f[i] != 0) nf.push_back({i, f[i]});
  rep(i, (int)g.size()) if (g[i] != 0) ng.push_back({i, g[i]});
  vector<mint> a(N, 0), b(N, 0);
  for (auto&& [i, x]: nf) {
    for (auto&& [j, y]: ng) {
      if (i + j >= N + 1) continue;
      mint xy = x * y;
      if (i + j < N) a[i + j] += xy;
      if (0 < i + j && i + j <= N) {
        b[i + j - 1] -= xy * (n * mint(i) + m * mint(j));
      }
    }
  }
  return differential_equation(a, b);
}
