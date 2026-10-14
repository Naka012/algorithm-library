// https://github.com/Naka012/algorithm-library/blob/main/formal_power_series/taylor_shift.hpp

/* f(x) -> f(x + c)*/

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

void fft(vector<mint> &a) {
    static constexpr int g = 3;
    int N = (int)a.size();
    int h = 0;
    while ((1 << h) < N) h++;

    static bool first = true;
    static mint sum_e[30];
    if (first) {
        first = false;
        mint es[30], ies[30];
        int cnt2 = __builtin_ctz(mint::Mod - 1);
        mint e = mint(g).pow((mint::Mod - 1) >> cnt2), ie = e.pow(mint::Mod - 2);
        for (int i = cnt2; i >= 2; i--) {
            es[i - 2] = e;
            ies[i - 2] = ie;
            e *= e;
            ie *= ie;
        }
        mint now = 1;
        for (int i = 0; i <= cnt2 - 2; i++) {
            sum_e[i] = es[i] * now;
            now *= ies[i];
        }
    }
    for (int ph = 1; ph <= h; ph++) {
        int w = 1 << (ph - 1), p = 1 << (h - ph);
        mint now = 1;
        for (int s = 0; s < w; s++) {
            int offset = s << (h - ph + 1);
            for (int i = 0; i < p; i++) {
                auto l = a[i + offset];
                auto r = a[i + offset + p] * now;
                a[i + offset] = l + r;
                a[i + offset + p] = l - r;
            }
            now *= sum_e[(~s ? __builtin_ctz(~s) : 32)];
        }
    }
}

void fft_inv(vector<mint> &a) {
    static constexpr int g = 3;
    int N = (int)a.size();
    int h = 0;
    while ((1 << h) < N) h++;

    static bool first = true;
    static mint sum_ie[30];
    if (first) {
        first = false;
        mint es[30], ies[30];
        int cnt2 = __builtin_ctz(mint::Mod - 1);
        mint e = mint(g).pow((mint::Mod - 1) >> cnt2), ie = e.pow(mint::Mod - 2);
        for (int i = cnt2; i >= 2; i--) {
            es[i - 2] = e;
            ies[i - 2] = ie;
            e *= e;
            ie *= ie;
        }
        mint now = 1;
        for (int i = 0; i <= cnt2 - 2; i++) {
            sum_ie[i] = ies[i] * now;
            now *= es[i];
        }
    }

    for (int ph = h; ph >= 1; ph--) {
        int w = 1 << (ph - 1), p = 1 << (h - ph);
        mint inow = 1;
        for (int s = 0; s < w; s++) {
            int offset = s << (h - ph + 1);
            for (int i = 0; i < p; i++) {
                auto l = a[i + offset];
                auto r = a[i + offset + p];
                a[i + offset] = l + r;
                a[i + offset + p] = (l - r) * inow;
            }
            inow *= sum_ie[(~s ? __builtin_ctz(~s) : 32)];
        }
    }
}

vector<mint> convolution(vector<mint> &A, vector<mint> &B) {
    ll lA = (int)A.size(), lB = (int)B.size(), d = lA + lB - 1, prime = 3;
    ll length = 0;
    while (1 << length < d) length++;
    length = 1 << length;
    A.resize(length, 0);
    B.resize(length, 0);
    fft(A);
    fft(B);
    rep(i, length) A[i] *= B[i];
    fft_inv(A);
    mint inv_N = mint(length).pow(mint::Mod - 2);
    rep(i, length) A[i] *= inv_N;
    A.resize(d);
    return A;
}

vector<mint> taylor_shift(vector<ll> &A, mint c){
    int N = (int)A.size();
    vector<mint> fact(N + 1, 1), invfact(N + 1, 1), powers(N + 1, 1), ret(N);
    for (ll i = 1; i < N + 1; i++){
        fact[i] = fact[i - 1] * i;
        powers[i] = powers[i - 1] * c;
    }
    invfact[N] = fact[N].pow(mint::Mod - 2);
    for (int i = N - 1; i >= 0; i--) invfact[i] = invfact[i + 1] * (i + 1);
    vector<mint> B(N), C(N);
    rep(i, N) B[N - i - 1] = A[i] * fact[i];
    rep(i, N) C[i] = powers[i] * invfact[i];
    auto tmp = convolution(B, C);
    rep(i, N) ret[i] = tmp[N - i - 1] * invfact[i];
    return ret;
}
