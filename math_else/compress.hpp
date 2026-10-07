template<class T> vector<T> compress(vector<T> &A){
    map<T, int> cnt;
    vector<T> tmp = A, ret((int)A.size());
    sort(tmp.begin(), tmp.end());
    int id = 0;
    for (int i = 0; i < (int)A.size(); i++) if (!cnt.count(tmp[i])){
        cnt[tmp[i]] = id;
        id++;
    }
    for (int i = 0; i < (int)A.size(); i++) ret[i] = cnt[A[i]];
    return ret;
}
