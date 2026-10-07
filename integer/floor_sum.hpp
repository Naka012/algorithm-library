ll floor_sum(ll n, ll m, ll a, ll b) {
    ll ret = 0;
    if (a >= m) {
        ret += (n - 1) * n * (a / m) / 2;
        a %= m;
    }
    if (b >= m) {
        ret += n * (b / m);
        b %= m;
    }

    ll y_max = (a * n + b) / m, x_max = (y_max * m - b);
    if (y_max == 0) return ret;
    ret += (n - (x_max + a - 1) / a) * y_max;
    ret += floor_sum(y_max, a, m, (a - x_max % a) % a);
    return ret;
}
