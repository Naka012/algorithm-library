// https://github.com/Naka012/algorithm-library/blob/main/hash/rolling_hash.hpp

const unsigned long long MOD = (1ull << 61) - 1;
struct rolling_hash {
    public : 
        struct hint{
            unsigned long long val;
            hint() {};
            hint(unsigned long long v) {
                if (v < MOD) val = v;
                else{
                    v %= MOD;
                    val = v;
                }
            }

            friend hint operator+(const hint& u, const hint& v){
                auto tmp = u.val + v.val;
                if (tmp >= MOD) tmp -= MOD;
                return tmp;
            }

            friend hint operator-(const hint& u, const hint& v){
                if (u.val < v.val) return u.val + MOD - v.val;
                return u.val - v.val;
                
            }

            friend hint operator*(const hint& u, const hint& v){
                auto ua = u.val >> 31, ub = u.val & ((1ull << 31) - 1), va = v.val >> 31, vb = v.val & ((1ull << 31) - 1);
                auto mid = ua * vb + va * ub;
                auto mida = mid >> 30, midb = mid & ((1ull << 30) - 1);
                auto ret = ua * va * 2ull + mida + (midb << 31) + ub * vb;
                ret = (ret >> 61) + (ret & ((1ull << 61) - 1));
                if (ret >= MOD) ret -= MOD;
                return ret;
            }

            hint pow(unsigned long long n){
                hint a = *this, ret = 1;
                while (n > 0){
                    if (n & 1) ret = ret * a;
                    a = a * a;
                    n >>= 1;
                }
                return ret;
            }
            friend bool operator==(const hint& u, const hint& v){return u.val == v.val;}
            friend bool operator!=(const hint& u, const hint& v){return u.val != v.val;}
        };

        const unsigned long long base = 20200213;

        rolling_hash(string s) {
            n = (int)s.size();
            ele = vector<hint>(n + 1, 0);
            powers = vector<hint>(n + 1, 1);
            for (int i = 0; i < n; i++){
                powers[i + 1] = powers[i] * base;
                ele[i + 1] = ele[i] * base + s[i];
            }
        }

        hint hash(int l, int r){
            return (ele[r] - ele[l] * powers[r - l]);
        }

        hint combine(hint& h1, hint& h2, int h2_length){
            return h1 * powers[h2_length] + h2;
        }

    private : 
        string _s;
        int n;
        vector<hint> ele, powers;
        hint power;
};
