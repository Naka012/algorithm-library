#include <bits/stdc++.h>
#define len(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
using namespace std;
template<typename T> using vc = vector<T>;
template<typename T> using vv = vc<vc<T>>;
using vi = vc<int>;using vvi = vv<int>; using vvvi = vv<vc<int>>;
using ll = long long;using vl = vc<ll>;using vvl = vv<ll>;
using uint = unsigned int;
using ull = unsigned long long;
using pii = pair<int, int>;
const double pi = 3.141592653589793;
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
// const int mod = 1000000007;
const int mod = 998244353;
inline bool inside(long long y, long long x, long long H, long long W) {return 0 <= y and y < H and 0 <= x and x < W; }

struct phash{
    inline size_t operator()(const pair<int,int> & p) const{
        const auto h1 = hash<int>()(p.first);
        const auto h2 = hash<int>()(p.second);
        return h1 ^ (h2 << 1);
    }
};

/*
miller rabin primality test
O((log N) ** 4) ?
Args:
    n (ll)
Returns:
    true or false

*/

ll pow_mod(ll a, ll d, ll m){
    ll ret = 1;
    while (d > 0){
        if (d & 1){
            ret *= a;
            ret %= m;
        }
        a = a * a % m;
        d >>= 1;
    }
    return ret;
}

bool miller_rabin(ll n)
{
    if (n == 2) return true;
    if (n < 2 || n % 2 == 0) return false;
    if(n == 3 || n == 5 || n == 7 || n == 11 || n == 13 || n == 17)return true;
    ll d = n - 1;
    int s = 0;
    while (d % 2 == 0){
        d /= 2;
        s += 1;
    }
    for (ll a : {2, 3, 5, 7, 11, 13, 17}){
        ll now = pow_mod(a, d, n);
        if (now == 1) continue;
        bool flag = true;
        for (int _ = 0; _ < s; _++){
            if (now == n - 1){
                flag = false;
                break;
            }
            now = now * now % n;
        }
        if (flag) return false;
        
    }
    return true;
}


namespace internal {
template <typename T>
using is_broadly_integral =
    typename conditional_t<is_integral_v<T> || is_same_v<T, __int128_t> ||
                               is_same_v<T, __uint128_t>,
                           true_type, false_type>::type;

template <typename T>
using is_broadly_signed =
    typename conditional_t<is_signed_v<T> || is_same_v<T, __int128_t>,
                           true_type, false_type>::type;

template <typename T>
using is_broadly_unsigned =
    typename conditional_t<is_unsigned_v<T> || is_same_v<T, __uint128_t>,
                           true_type, false_type>::type;

#define ENABLE_VALUE(x) \
  template <typename T> \
  constexpr bool x##_v = x<T>::value;

ENABLE_VALUE(is_broadly_integral);
ENABLE_VALUE(is_broadly_signed);
ENABLE_VALUE(is_broadly_unsigned);
#undef ENABLE_VALUE

#define ENABLE_HAS_TYPE(var)                                   \
  template <class, class = void>                               \
  struct has_##var : false_type {};                            \
  template <class T>                                           \
  struct has_##var<T, void_t<typename T::var>> : true_type {}; \
  template <class T>                                           \
  constexpr auto has_##var##_v = has_##var<T>::value;

#define ENABLE_HAS_VAR(var)                                     \
  template <class, class = void>                                \
  struct has_##var : false_type {};                             \
  template <class T>                                            \
  struct has_##var<T, void_t<decltype(T::var)>> : true_type {}; \
  template <class T>                                            \
  constexpr auto has_##var##_v = has_##var<T>::value;

}  // namespace internal
namespace internal {

#include <cassert>
#include <utility>
#include <vector>
using namespace std;

// a mod p
template <typename T>
T safe_mod(T a, T p) {
  a %= p;
  if constexpr (is_broadly_signed_v<T>) {
    if (a < 0) a += p;
  }
  return a;
}

// 返り値：pair(g, x)
// s.t. g = gcd(a, b), xa = g (mod b), 0 <= x < b/g
template <typename T>
pair<T, T> inv_gcd(T a, T p) {
  static_assert(is_broadly_signed_v<T>);
  a = safe_mod(a, p);
  if (a == 0) return {p, 0};
  T b = p, x = 1, y = 0;
  while (a != 0) {
    T q = b / a;
    swap(a, b %= a);
    swap(x, y -= q * x);
  }
  if (y < 0) y += p / b;
  return {b, y};
}

// 返り値 : a^{-1} mod p
// gcd(a, p) != 1 が必要
template <typename T>
T inv(T a, T p) {
  static_assert(is_broadly_signed_v<T>);
  a = safe_mod(a, p);
  T b = p, x = 1, y = 0;
  while (a != 0) {
    T q = b / a;
    swap(a, b %= a);
    swap(x, y -= q * x);
  }
  assert(b == 1);
  return y < 0 ? y + p : y;
}

// T : 底の型
// U : T*T がオーバーフローしない かつ 指数の型
template <typename T, typename U>
T modpow(T a, U n, T p) {
  a = safe_mod(a, p);
  T ret = 1 % p;
  while (n != 0) {
    if (n % 2 == 1) ret = U(ret) * a % p;
    a = U(a) * a % p;
    n /= 2;
  }
  return ret;
}

// 返り値 : pair(rem, mod)
// 解なしのときは {0, 0} を返す
template <typename T>
pair<T, T> crt(const vector<T>& r, const vector<T>& m) {
  static_assert(is_broadly_signed_v<T>);
  assert(r.size() == m.size());
  int n = int(r.size());
  T r0 = 0, m0 = 1;
  for (int i = 0; i < n; i++) {
    assert(1 <= m[i]);
    T r1 = safe_mod(r[i], m[i]), m1 = m[i];
    if (m0 < m1) swap(r0, r1), swap(m0, m1);
    if (m0 % m1 == 0) {
      if (r0 % m1 != r1) return {0, 0};
      continue;
    }
    auto [g, im] = inv_gcd(m0, m1);
    T u1 = m1 / g;
    if ((r1 - r0) % g) return {0, 0};
    T x = (r1 - r0) / g % u1 * im % u1;
    r0 += x * m0;
    m0 *= u1;
    if (r0 < 0) r0 += m0;
  }
  return {r0, m0};
}

}  // namespace internal

template <typename Int, typename UInt, typename Long, typename ULong, int id>
struct ArbitraryLazyMontgomeryModIntBase {
  using mint = ArbitraryLazyMontgomeryModIntBase;

  inline static UInt mod;
  inline static UInt r;
  inline static UInt n2;
  static constexpr int bit_length = sizeof(UInt) * 8;

  static UInt get_r() {
    UInt ret = mod;
    while (mod * ret != 1) ret *= UInt(2) - mod * ret;
    return ret;
  }
  static void set_mod(UInt m) {
    assert(m < (UInt(1u) << (bit_length - 2)));
    assert((m & 1) == 1);
    mod = m, n2 = -ULong(m) % m, r = get_r();
  }
  UInt a;

  ArbitraryLazyMontgomeryModIntBase() : a(0) {}
  ArbitraryLazyMontgomeryModIntBase(const Long &b)
      : a(reduce(ULong(b % mod + mod) * n2)){};

  static UInt reduce(const ULong &b) {
    return (b + ULong(UInt(b) * UInt(-r)) * mod) >> bit_length;
  }

  mint &operator+=(const mint &b) {
    if (Int(a += b.a - 2 * mod) < 0) a += 2 * mod;
    return *this;
  }
  mint &operator-=(const mint &b) {
    if (Int(a -= b.a) < 0) a += 2 * mod;
    return *this;
  }
  mint &operator*=(const mint &b) {
    a = reduce(ULong(a) * b.a);
    return *this;
  }
  mint &operator/=(const mint &b) {
    *this *= b.inverse();
    return *this;
  }

  mint operator+(const mint &b) const { return mint(*this) += b; }
  mint operator-(const mint &b) const { return mint(*this) -= b; }
  mint operator*(const mint &b) const { return mint(*this) *= b; }
  mint operator/(const mint &b) const { return mint(*this) /= b; }

  bool operator==(const mint &b) const {
    return (a >= mod ? a - mod : a) == (b.a >= mod ? b.a - mod : b.a);
  }
  bool operator!=(const mint &b) const {
    return (a >= mod ? a - mod : a) != (b.a >= mod ? b.a - mod : b.a);
  }
  mint operator-() const { return mint(0) - mint(*this); }
  mint operator+() const { return mint(*this); }

  mint pow(ULong n) const {
    mint ret(1), mul(*this);
    while (n > 0) {
      if (n & 1) ret *= mul;
      mul *= mul, n >>= 1;
    }
    return ret;
  }

  friend ostream &operator<<(ostream &os, const mint &b) {
    return os << b.get();
  }

  friend istream &operator>>(istream &is, mint &b) {
    Long t;
    is >> t;
    b = ArbitraryLazyMontgomeryModIntBase(t);
    return (is);
  }

  mint inverse() const {
    Int x = get(), y = get_mod(), u = 1, v = 0;
    while (y > 0) {
      Int t = x / y;
      swap(x -= t * y, y);
      swap(u -= t * v, v);
    }
    return mint{u};
  }

  UInt get() const {
    UInt ret = reduce(a);
    return ret >= mod ? ret - mod : ret;
  }

  static UInt get_mod() { return mod; }
};

// id に適当な乱数を割り当てて使う
template <int id>
using ArbitraryLazyMontgomeryModInt =
    ArbitraryLazyMontgomeryModIntBase<int, unsigned int, long long,
                                      unsigned long long, id>;
template <int id>
using ArbitraryLazyMontgomeryModInt64bit =
    ArbitraryLazyMontgomeryModIntBase<long long, unsigned long long, __int128_t,
                                      __uint128_t, id>;

namespace fast_factorize {

template <typename T, typename U>
bool miller_rabin(const T& n, vector<T> ws) {
  if (n <= 2) return n == 2;
  if (n % 2 == 0) return false;

  T d = n - 1;
  while (d % 2 == 0) d /= 2;
  U e = 1, rev = n - 1;
  for (T w : ws) {
    if (w % n == 0) continue;
    T t = d;
    U y = internal::modpow<T, U>(w, t, n);
    while (t != n - 1 && y != e && y != rev) y = y * y % n, t *= 2;
    if (y != rev && t % 2 == 0) return false;
  }
  return true;
}

bool miller_rabin_u64(unsigned long long n) {
  return miller_rabin<unsigned long long, __uint128_t>(
      n, {2, 325, 9375, 28178, 450775, 9780504, 1795265022});
}

template <typename mint>
bool miller_rabin(unsigned long long n, vector<unsigned long long> ws) {
  if (n <= 2) return n == 2;
  if (n % 2 == 0) return false;

  if (mint::get_mod() != n) mint::set_mod(n);
  unsigned long long d = n - 1;
  while (~d & 1) d >>= 1;
  mint e = 1, rev = n - 1;
  for (unsigned long long w : ws) {
    if (w % n == 0) continue;
    unsigned long long t = d;
    mint y = mint(w).pow(t);
    while (t != n - 1 && y != e && y != rev) y *= y, t *= 2;
    if (y != rev && t % 2 == 0) return false;
  }
  return true;
}

bool is_prime(unsigned long long n) {
  using mint32 = ArbitraryLazyMontgomeryModInt<96229631>;
  using mint64 = ArbitraryLazyMontgomeryModInt64bit<622196072>;

  if (n <= 2) return n == 2;
  if (n % 2 == 0) return false;
  if (n < (1uLL << 30)) {
    return miller_rabin<mint32>(n, {2, 7, 61});
  } else if (n < (1uLL << 62)) {
    return miller_rabin<mint64>(
        n, {2, 325, 9375, 28178, 450775, 9780504, 1795265022});
  } else {
    return miller_rabin_u64(n);
  }
}

}  // namespace fast_factorize

using fast_factorize::is_prime;
