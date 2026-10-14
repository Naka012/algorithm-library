// https://github.com/Naka012/algorithm-library/blob/main/graph/eulertour.hpp

/*
depth_euler : オイラーツアーの順番で回った時の頂点の深さの列
place : その頂点がdepthの何番目にいるか 必ず二つ入っている

*/

vector<int> depth_euler;
map<int, vector<int>> place;
vector<bool> seen(200200, false);
int depth = 0, cnt = 0;

void dfs(int v, vector<vector<int>> &g){
    seen[v] = true;
    depth_euler.push_back(depth);
    place[v].push_back(cnt);
    depth++;
    for(auto nxt : g[v]){
        if (!seen[nxt]){
            cnt++;
            dfs(nxt, g);
        }
    }
    depth--;
    cnt++;
    depth_euler.push_back(depth);
    place[v].push_back(cnt);
}
