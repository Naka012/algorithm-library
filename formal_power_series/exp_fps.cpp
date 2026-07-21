// (⁠◕⁠ᴗ⁠◕⁠✿⁠)
 
#include <bits/stdc++.h>
#define rep(i, n) for (ll i = 0; i < (n); i++)
#define srep(i, s, n) for (ll i = s; i < (n); i++)
#define len(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
using namespace std;
template<typename T> using vc = vector<T>;
template<typename T> using vv = vc<vc<T>>;
using vi = vc<int>;using vvi = vv<int>; using vvvi = vv<vi>;
using ll = long long;using vl = vc<ll>;using vvl = vv<ll>; using vvvl = vv<vl>;
using ld = long double; using vld = vc<ld>; using vvld = vc<vld>; using vvvld = vc<vvld>;
using uint = unsigned int;
using ull = unsigned long long;
const ld pi = 3.141592653589793;
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
// const ll mod = 1000000007;
const ll mod = 998244353;
inline bool inside(long long y, long long x, long long H, long long W) {return 0 <= (y) and (y) < (H) and 0 <= (x) and (x) < (W); }

#define debug(var)  do{std::cout << #var << " : \n";view(var);}while(0)
template<typename T> void view(T e){cout << e << endl;}
template<typename T> void view(const vc<T>& v){for(const auto& e : v){ cout << e << " "; } cout << endl;}
template<typename T> void view(const vv<T>& vv){ for(const auto& v : vv){ view(v); } }


struct modint {
    int Mod = mod;
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
        int a = val, b = mod, u = 1, v = 0, t;
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

using mint = modint;

void fft(vc<mint> &a) {
    static constexpr int g = 3;
    int N = len(a);
    int h = 0;
    while ((1 << h) < N) h++;

    static bool first = true;
    static mint sum_e[30];
    if (first) {
        first = false;
        mint es[30], ies[30];
        int cnt2 = __builtin_ctz(mod - 1);
        mint e = mint(g).pow((mod - 1) >> cnt2), ie = e.pow(mod - 2);
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

void fft_inv(vc<mint> &a) {
    static constexpr int g = 3;
    int N = len(a);
    int h = 0;
    while ((1 << h) < N) h++;

    static bool first = true;
    static mint sum_ie[30];
    if (first) {
        first = false;
        mint es[30], ies[30];
        int cnt2 = __builtin_ctz(mod - 1);
        mint e = mint(g).pow((mod - 1) >> cnt2), ie = e.pow(mod - 2);
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

vc<mint> convolution(vc<mint> &A, vc<mint> &B) {
    ll lA = len(A), lB = len(B), d = lA + lB - 1, prime = 3;
    ll length = 0;
    while (1 << length < d) length++;
    length = 1 << length;
    A.resize(length, 0);
    B.resize(length, 0);
    fft(A);
    fft(B);
    rep(i, length) A[i] *= B[i];
    fft_inv(A);
    mint inv_N = mint(length).pow(mod - 2);
    rep(i, length) A[i] *= inv_N;
    A.resize(d);
    return A;
}

vc<mint> inv_fps(vc<mint> &f){
    assert(f[0] != 0);
    ll N = len(f);
    int cnt = 0;
    rep(i, N) if (f[i] != 0) cnt++;
    if (cnt <= 200){
        vc<pair<int, mint>> nf;
        srep(i, 1, N) if (f[i] != 0) nf.push_back({i, f[i]});
        vc<mint> g(N);
        mint inv_f0 = 1 / f[0];
        g[0] = inv_f0;
        srep(i, 1, N){
            mint tmp = 0;
            for (auto [j, fj] : nf) {
                if (j > i) break;
                tmp -= fj * g[i - j];
            }
            g[i] = tmp * inv_f0;
        }
        return g;
    }
    vc<mint> g = {1 / f[0]};
    ll ln = 1;
    while (ln < N){
        ll length = 2 * ln;
        vc<mint> ng(length, 0), nf(length, 0);
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
        srep(i, ln, length) g.push_back(nf[i] * c);
        ln *= 2;
    }
    g.resize(N);
    return g;
}

vc<mint> differential_fps(vc<mint> &f){
    int N = len(f);
    vc<mint> ret(N - 1);
    for (ll i = 1; i < N; i++) ret[i - 1] = i * f[i];
    return ret;
}

vc<mint> integral_fps(vc<mint> &f, mint c){
    int N = len(f);
    vc<mint> ret(N + 1, c);
    rep(i, N) ret[i + 1] = f[i] / (i + 1);
    return ret;
}

vc<mint> log_fps(vc<mint> &f){
    int N = len(f);
    assert(f[0] == 1);
    auto f_dif = differential_fps(f), f_inv = inv_fps(f);
    auto log_f_dif = convolution(f_dif, f_inv);
    log_f_dif.resize(N - 1);
    mint c = 0;
    return integral_fps(log_f_dif, c);
}

vc<mint> exp_fps(vc<mint> &f){
    assert(f[0] == 0);
    ll N = len(f);
    int cnt = 0;
    rep(i, N) if (f[i] != 0) cnt++;
    if (cnt <= 300){
        vc<pair<int, mint>> nf;
        srep(i, 1, N) if (f[i] != 0) nf.push_back({i - 1, i * f[i]});
        vc<mint> g(N);
        g[0] = 1;
        srep(i, 1, N){
            mint tmp = 0;
            for (auto [j, fj] : nf){
                if (j + 1 > i) break;
                tmp += fj * g[i - (j + 1)];
            }
            g[i] = tmp * mint(i).inverse();
        }
        return g;
    }
    vc<mint> g = {1};
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
