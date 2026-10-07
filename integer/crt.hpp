/*
return min(x) s.t. x = a (mod1) && x = b (mod2)
*/
ll extra_gcd(ll a, ll b, ll &x, ll &y){
    if (b == 0){
        x = 1;
        y = 0;
        return a;
    }
    ll ret = extra_gcd(b, a % b, y, x);
    y -= a / b * x;

    return ret;
}

ll crt(ll mod1, ll a, ll mod2, ll b){
    if (mod1 < mod2){
        swap(mod1, mod2);
        swap(a, b);
    }
    if (mod1 % mod2 == 0 && a % mod2 != b) return -1;
    ll x, y, g;
    g = extra_gcd(mod1, mod2, x, y);
    x %= mod2;
    if (x < 0) x += mod2;
    if ((b - a) % g) return -1;
    ll m = mod2 / g, l = mod1 * m, tmp = (b - a) / g % m * x % m;
    ll ret = tmp * mod1 + a;
    if (ret < 0) ret += l;
    return ret;
}
