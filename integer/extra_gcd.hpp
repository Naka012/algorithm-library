/*
ax + by = gcd(a, b) なる x, y

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
