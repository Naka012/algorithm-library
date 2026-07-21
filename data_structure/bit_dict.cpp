#include <bits/stdc++.h>
// #include <atcoder/all>
// using namespace atcoder;
// using mint = modint1000000007;
// using mint = modint998244353;
// using vmint = vc<mint>;using vvmint = vc<vmint>;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define srep(i, s, n) for (int i = s; i < n; i++)
#define drep(i, n) for (int i = n; i >= 0; i--)
#define dsrep(i, s, n) for (int i = s; i >= n; i--)
#define len(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define YES(n) cout << ((n) ? "YES" : "NO" ) << endl
#define Yes(n) cout << ((n) ? "Yes" : "No" ) << endl
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

// ばぐってます

struct bit_dict {
    public :
        bit_dict(int n) : _n(n){
            lenl = (int)sqrt(log2(_n));
            lens = (int)log2(_n) / 2;
            L = vi(lenl, 0);
            S = vi(lens, 0);
            P = map<string, int>();
            rep(i, 1 << lens){
                int cnt = 0;
                string bit;
                rep(j, lens){
                    if (i >> j & 1){
                        bit += "1";
                        cnt++;
                    }
                    else bit += "0";
                }
                P[bit] = cnt;
            }
        }
    
    void build(string &st){
        B = st;
        int now = 0;
        rep(i, _n){
            if (i % lenl == 0) L[i % lenl] = now;
            if (i % lens == 0) S[i % lens] = now;
            if (B[i] == '1') now += 1;
        }
    }

    int rank(int k, int i){
        int x = (i + lenl - 1) / lenl, y = (i + lens - 1) / lens;
        if (k == 1) return L[x] + S[y] + P[B.substr(y * lens, i - y * lens)];
        return i - L[x] + S[y] + P[B.substr(y * lens, i - y * lens)];
    }

    int select(int k, int i){
        int top = _n, bottom = 0, mid;
        while (top - bottom > 1){
            mid = (top + bottom) / 2;
            if (rank(k, mid) <= i) bottom = mid;
            else top = mid;
        }
        return bottom;
    }

    
    private :
        int _n, lenl, lens;
        vi L, S;
        map<string, int> P;
        string B;
};

