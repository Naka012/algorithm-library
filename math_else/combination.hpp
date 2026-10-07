ll C(int n, int m) {
    m = min(m, n - m);
    ll res = 1;
    for (int i = 0; i < m; i++){
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}
