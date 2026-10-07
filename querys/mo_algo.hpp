/*
mo mo
O(???)
でもまにあうしはやい

query(l, r) := [l, r)
out(i) := answer i th query

*/

ll hilbertorder(int x, int y, ll maxn) {
  ll rx, ry, d = 0;
  for (ll s = maxn >> 1; s; s >>= 1) {
    rx = (x & s)>0, ry = (y & s)>0;
    d += s * s * ((rx * 3) ^ ry);
    if (ry) continue;
    if (rx) {
      x = maxn - 1 - x;
      y = maxn - 1 - y;
    }
    swap(x, y);
  }
  return d;
}

void mo_algo(int N, vector<pair<int, int>> &querys, auto add_l, auto add_r, auto erase_l, auto erase_r, auto out){
    int Q = (int)querys.size();
    vector<int> order(Q);
    iota(order.begin(), order.end(), 0);
    ll maxn = 1;
    while (maxn < N) maxn <<= 1;
    vector<ll> eval(Q);
    for (int i = 0; i < Q; i++) eval[i] = hilbertorder(querys[i].first, querys[i].second, maxn);

    sort(order.begin(), order.end(), [&](int i, int j) {
        return eval[i] < eval[j];
    });

    int nl = 0, nr = 0;
    for(int i : order) {
        auto& [l, r] = querys[i];
        while(nl > l) add_l(--nl);
        while(nr < r) add_r(nr++);
        while(nl < l) erase_l(nl++);
        while(nr > r) erase_r(--nr);
        out(i);
    }
    return;
}
