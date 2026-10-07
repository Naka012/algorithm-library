// ばぐってます

struct bit_dict {
    public :
        bit_dict(int n) : _n(n){
            lenl = (int)sqrt(log2(_n));
            lens = (int)log2(_n) / 2;
            L = vector<int>(lenl, 0);
            S = vector<int>(lens, 0);
            P = map<string, int>();
            rep(i, 1 << lens){
                int cnt = 0;
                string bit;
                rep(j, lens){
                    if (i >> j & 1){
                        bit += "1";
                        cnt++;
                    }
                    else bit += "0";
                }
                P[bit] = cnt;
            }
        }
    
    void build(string &st){
        B = st;
        int now = 0;
        rep(i, _n){
            if (i % lenl == 0) L[i % lenl] = now;
            if (i % lens == 0) S[i % lens] = now;
            if (B[i] == '1') now += 1;
        }
    }

    int rank(int k, int i){
        int x = (i + lenl - 1) / lenl, y = (i + lens - 1) / lens;
        if (k == 1) return L[x] + S[y] + P[B.substr(y * lens, i - y * lens)];
        return i - L[x] + S[y] + P[B.substr(y * lens, i - y * lens)];
    }

    int select(int k, int i){
        int top = _n, bottom = 0, mid;
        while (top - bottom > 1){
            mid = (top + bottom) / 2;
            if (rank(k, mid) <= i) bottom = mid;
            else top = mid;
        }
        return bottom;
    }

    
    private :
        int _n, lenl, lens;
        vector<int> L, S;
        map<string, int> P;
        string B;
};
