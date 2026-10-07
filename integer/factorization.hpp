/*
素因数分解
O(sqrt N)

Args:
    N (ll): 元の数

Return:
    factors (vector<pair<int, int>>): pair(i, j) := i が j 個含まれる

*/

vector<pair<ll, ll>> factorization(ll &N){
    vector<pair<ll, ll>> factors;
    ll tmp = N;
    for (ll i = 2; i * i <= N + 1; i++){
        if (tmp % i == 0){
            int cnt = 0;
            while (tmp % i == 0){
                tmp /= i;
                cnt += 1;
            }
            factors.push_back({i, cnt});
        }
    }
    if (tmp != 1){
        factors.push_back({tmp, 1});
    }
    if ((int)factors.size() == 0){
        factors.push_back({N, 1});
    }
    return factors;
}
