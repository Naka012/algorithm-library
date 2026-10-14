// https://github.com/Naka012/algorithm-library/blob/main/hash/hash_int.hpp

const unsigned long long MOD = (1ull << 61) - 1;
const unsigned long long base = 20200213;
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
