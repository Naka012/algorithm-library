// https://github.com/Naka012/algorithm-library/blob/main/formal_power_series/pow_fps.hpp
// 出典 (fft, fft_inv): https://github.com/atcoder/ac-library/blob/v1.3/atcoder/convolution.hpp
// 出典 (inv_fps): https://github.com/maspypy/library/blob/main/poly/fps_inv.hpp
// 出典 (exp_fps の sparse 部分): https://github.com/maspypy/library/blob/main/poly/fps_exp.hpp
// 出典 (pow_fps): https://github.com/maspypy/library/blob/main/poly/fps_pow.hpp

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

vector<mint> inv_fps(vector<mint> &f){
    assert(f[0] != 0);
    ll N = (int)f.size();
    int cnt = 0;
    rep(i, N) if (f[i] != 0) cnt++;
    if (cnt <= 200){
        vector<pair<int, mint>> nf;
        for (ll i = 1; i < N; i++) if (f[i] != 0) nf.push_back({i, f[i]});
        vector<mint> g(N);
        mint inv_f0 = 1 / f[0];
        g[0] = inv_f0;
        for (ll i = 1; i < N; i++){
            mint tmp = 0;
            for (auto [j, fj] : nf) {
                if (j > i) break;
                tmp -= fj * g[i - j];
            }
            g[i] = tmp * inv_f0;
        }
        return g;
    }
    vector<mint> g = {1 / f[0]};
    ll ln = 1;
    while (ln < N){
        ll length = 2 * ln;
        vector<mint> ng(length, 0), nf(length, 0);
        rep(i, ln) ng[i] = g[i];
        rep(i, min(N, 2 * ln)) nf[i] = f[i];
        fft(ng);
        fft(nf);
        rep(i, length) nf[i] *= ng[i];
        fft_inv(nf);
        rep(i, ln) nf[i] = 0;
        fft(nf);
        rep(i, length) nf[i] *= ng[i];
        fft_inv(nf);
        mint c = mint(-1) / (length * length);
        for (ll i = ln; i < length; i++) g.push_back(nf[i] * c);
        ln *= 2;
    }
    g.resize(N);
    return g;
}

vector<mint> differential_fps(vector<mint> &f){
    int N = (int)f.size();
    vector<mint> ret(N - 1);
    for (ll i = 1; i < N; i++) ret[i - 1] = i * f[i];
    return ret;
}

vector<mint> integral_fps(vector<mint> &f, mint c){
    int N = (int)f.size();
    vector<mint> ret(N + 1, c);
    rep(i, N) ret[i + 1] = f[i] / (i + 1);
    return ret;
}

vector<mint> log_fps(vector<mint> &f){
    int N = (int)f.size();
    assert(f[0] == 1);
    auto f_dif = differential_fps(f), f_inv = inv_fps(f);
    auto log_f_dif = convolution(f_dif, f_inv);
    log_f_dif.resize(N - 1);
    mint c = 0;
    return integral_fps(log_f_dif, c);
}

vector<mint> exp_fps(vector<mint> &f){
    assert(f[0] == 0);
    ll N = (int)f.size();
    int cnt = 0;
    rep(i, N) if (f[i] != 0) cnt++;
    if (cnt <= 300){
        vector<pair<int, mint>> nf;
        for (ll i = 1; i < N; i++) if (f[i] != 0) nf.push_back({i - 1, i * f[i]});
        vector<mint> g(N);
        g[0] = 1;
        for (ll i = 1; i < N; i++){
            mint tmp = 0;
            for (auto [j, fj] : nf){
                if (j + 1 > i) break;
                tmp += fj * g[i - (j + 1)];
            }
            g[i] = tmp * mint(i).inverse();
        }
        return g;
    }
    vector<mint> g = {1};
    ll ln = 1;
    while (ln < N){
        g.resize(2 * ln, 0);
        auto log_g = log_fps(g);
        rep(i, 2 * ln) log_g[i] *= -1;
        rep(i, min(N, 2 * ln)) log_g[i] += f[i];
        log_g[0] += 1;
        g = convolution(g, log_g);
        g.resize(2 * ln);
        ln *= 2;
    }
    g.resize(N);
    return g;
}

vector<mint> pow_fps(vector<mint> &f, ll M){
    ll N = (int)f.size();
    if (M == 0){
        vector<mint> g(N, 0);
        g[0] = 1;
        return g;
    }
    ll nonzero = 0;
    while (nonzero < N && f[nonzero] == 0) nonzero++;
    if (nonzero >= (N + M - 1) / M) return vector<mint>(N, 0);
    mint f0 = f[nonzero], f0_inv = f0.pow(mint::Mod - 2);
    vector<mint> tmp(f.begin() + nonzero, f.end());
    for (auto &x : tmp) x *= f0_inv;
    int cnt = 0, n = (int)tmp.size();
    rep(i, n) if (tmp[i] != 0) cnt++;
    if (cnt <= 100){
        vector<mint> ng(n, 0);
        ng[0] = 1;
        vector<pair<int, mint>> nf;
        for (ll i = 1; i < n; i++) if (tmp[i] != 0) nf.push_back({i, tmp[i]});
        rep(i, n - 1) {
            mint& x = ng[i + 1];
            for (auto&& [d, cf]: nf) {
                if (d > i + 1) break;
                mint t = cf * ng[i - d + 1];
                x += t * (M * mint(d) - mint(i - d + 1));
            }
            x /= (i + 1);
        }
        swap(tmp, ng);
    }else{
        auto log_f = log_fps(tmp);
        for (auto &x : log_f) x *= mint(M);
        tmp = exp_fps(log_f);
    }
    vector<mint> g(N, 0);
    nonzero *= M;
    f0 = f0.pow(M);
    rep(i, min((int)tmp.size(), (int)(N - nonzero))) g[nonzero + i] = tmp[i] * f0;
    return g;
}
