// 出典: https://github.com/ei1333/library/blob/master/graph/mst/manhattan-mst.hpp

/*
頂点が平面上にあり、マンハッタン距離を辺の重みにしたときの
最小全域木 の候補辺列挙

O(|V| log |V|)
*/

vector<tuple<ll, int, int>> manhattanMST(vector<pair<ll, ll>> &points){
    int N = (int)points.size();
    vector<tuple<ll, int, int>> ret;
    vector<int> idx(N);
    iota(idx.begin(), idx.end(), 0);
    for (int s = 0; s < 2; s++) {
        for (int t = 0; t < 2; t++) {
            sort(idx.begin(), idx.end(), [&](int i, int j) { 
                return points[i].first + points[i].second < points[j].first + points[j].second;
                }
            );
            map<ll, int> sweep;

            for (int i : idx) {
                for (auto it = sweep.lower_bound(-points[i].second); it != sweep.end(); it = sweep.erase(it)) {
                    int j = it->second;
                    if (points[i].first - points[j].first < points[i].second - points[j].second) break;
                    ret.push_back({abs(points[i].first - points[j].first) + abs(points[i].second - points[j].second), i, j});
                }
                sweep[-points[i].second] = i;
            }
            for (auto &p : points) swap(p.first, p.second);
        }
        for (auto &p : points) p.first = -p.first;
    }

    sort(ret.begin(), ret.end());
    return ret;
}
