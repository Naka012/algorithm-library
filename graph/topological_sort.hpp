/*
topological sort
O(|V| + |E|)

Args:
    N (int) : graph size
    g (vector<vector<int>>) : g[i] := edge (i to j)
    enterdeg (vector<int>) : enterdeg[i] := enter degree of i

Returns:
    bool : false -> exist sycle
           true -> not ""
    vector<int> : result
*/

tuple<bool, vector<int>> topological_sort(int &N, vector<vector<int>> &g, vector<int> &enterdeg){
    priority_queue<int, vector<int>, greater<int>> q;
    for (int i = 0; i < N; i++){
        if (enterdeg[i] == 0) q.push(i);
    }
    vector<int> ret;
    while (!q.empty()){
        int now = q.top(); q.pop();
        ret.push_back(now);
        for (auto nxt : g[now]){
            enterdeg[nxt] -= 1;
            if (enterdeg[nxt] == 0) q.push(nxt);
        }
    }
    if ((int)ret.size() == N) return {true, ret};
    return {false, {}};
}
