struct RollbackUnionFind{
    public : 
        RollbackUnionFind(int n) : _n(n){
            root = vector<int>(_n, -1);
        }

        int find(int x){
            if (root[x] < 0) return x;
            return find(root[x]);
        }

        void unite(int x, int y){
            x = find(x);
            y = find(y);
            history.push_back({x, root[x]});
            history.push_back({y, root[y]});
            if (x != y){
                if (-root[x] < -root[y]) swap(x, y);
                root[x] += root[y];
                root[y] = x;
            }
        }

        bool same(int x, int y){
            return find(x) == find(y);
        }

        int size(int x){
            return -root[find(x)];
        }

        void undo(){
            root[history.back().first] = history.back().second;
            history.pop_back();
            root[history.back().first] = history.back().second;
            history.pop_back();
        }

        int nw(){
            return (int)history.size() >> 1;
        }

        void snapshot(){
            sp = nw();
        }

        void rollback(int t = -1){
            if (t == -1) t = sp;
            while (nw() > t) undo();
        }

    private : 
        int _n, sp;
        vector<int> root;
        vector<pair<int, int>> history;
};
