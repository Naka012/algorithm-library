// (⁠◕⁠ᴗ⁠◕⁠✿⁠)
 
#include <bits/stdc++.h>
#define rep(i, n) for (ll i = 0; i < (n); i++)
#define srep(i, s, n) for (ll i = s; i < (n); i++)
#define len(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
using namespace std;
template<typename T> using vc = vector<T>;
template<typename T> using vv = vc<vc<T>>;
template<typename T> using vvv = vv<vc<T>>;
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

// 小さいほうの個数がt
struct BallanceSet{
    public :
        BallanceSet(int _t) : t(_t){}
        
        void ballance(){
            while (len(x) < t && len(y)){
                auto it = y.begin();
                x.insert(*it);
                sx += *it;
                sy -= *it;
                y.erase(it);
            }
            if (len(x) == 0 || len(y) == 0) return;

            while (true){
                auto xit = x.end(); xit--;
                auto yit = y.begin();
                ll ex = *xit, ey = *yit;
                if (ex <= ey) break;
                sx += ey - ex;
                sy += ex - ey;
                x.erase(xit);
                y.erase(yit);
                x.insert(ey);
                y.insert(ex);
            }
        }

        void add(ll p){
            y.insert(p);
            sy += p;
            ballance();
        }

        void erase(ll p){
            auto xit = x.find(p);
            if (xit != x.end()){
                x.erase(xit);
                sx -= p;
            }else{
                y.erase(y.find(p));
                sy -= p;
                auto it = x.end(); it--;
                sy += *it;
                sx -= *it;
                y.insert(*it);
                x.erase(it);
            }
            ballance();
        }

        ll lower_sum(){return sx;}
        ll upper_sum(){return sy;}
    private : 
        multiset<ll> x, y;
        ll sx = 0, sy = 0;
        int t;
};
