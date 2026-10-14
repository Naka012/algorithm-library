// https://github.com/Naka012/algorithm-library/blob/main/integer/BsGs.hpp

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

ll BsGs(ll x, ll y, ll md){
    unordered_map<ll, ll> babys;
    ll nw = 1, sq = sqrt(md) + 1;
    for (ll i = 0; i < sq; i++){
        if (!babys.count(nw)) babys[nw] = i;
        nw = nw * x % md;
    }
    ll giant = y, inv = pow_mod(pow_mod(x, md - 2, md), sq, md);
    for (int i = 0; i <= sq; i ++){
        if (babys.count(giant)) return babys[giant] + i * sq;
        giant = giant * inv % md;
    }
    return -1;
}
