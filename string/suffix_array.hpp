// https://github.com/Naka012/algorithm-library/blob/main/string/suffix_array.hpp

struct SuffixArray {
    string S;
    vector<int> arr;
    SuffixArray(string &s) : S(s){
        arr.resize((int)S.size() + 1);
        vector<int> rank((int)S.size() + 1), tmp((int)S.size() + 1);
        rep(i, (int)S.size() + 1){
            arr[i] = i;
            if (i < (int)S.size()) rank[i] = S[i];
            else rank[i] = -1;
        }
        for (int k = 1; k <= (int)S.size(); k *= 2){
            auto f = [&](auto i, auto j){
                if (rank[i] != rank[j]) return rank[i] < rank[j];
                int ni = -1, nj = -1;
                if (i + k <= (int)S.size()) ni = rank[i + k];
                if (j + k <= (int)S.size()) nj = rank[j + k];
                return ni < nj;
            };
            sort(arr.begin(), arr.end(), f);
            tmp[arr[0]] = 0;
            for (ll i = 1; i < (int)S.size() + 1; i++){
                tmp[arr[i]] = tmp[arr[i - 1]] + f(arr[i - 1], arr[i]);
            }
            swap(rank, tmp);
        }
    }

    int operator[](int i)const{return arr[i];}

    int lower_bound(string &t){
        int top = (int)S.size() + 1, bottom = -1;
        while (top - bottom > 1){
            int mid = (top + bottom) / 2;
            if (S.compare(arr[mid], (int)t.size(), t) >= 0) top = mid;
            else bottom = mid;
        }
        return top;
    }

    int upper_bound(string &t){
        int top = (int)S.size() + 1, bottom = -1;
        while (top - bottom > 1){
            int mid = (top + bottom) / 2;
            if (S.compare(arr[mid], (int)t.size(), t) <= 0) bottom = mid;
            else top = mid;
        }
        return top;
    }
};
