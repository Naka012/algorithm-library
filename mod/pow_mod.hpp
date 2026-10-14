// https://github.com/Naka012/algorithm-library/blob/main/mod/pow_mod.hpp

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
