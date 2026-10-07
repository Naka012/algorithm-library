/*
dot
Args:
    A (vector<vector<T>>)
    B (vector<vector<T>>)
Returns:
    A * B (vector<vector<T>>)

multidot
Args:
    A (vector<vector<T>>)
    N (ll)
Returns:
    A ** N (vector<vector<T>>)
*/

template<typename T> vector<vector<T>> dot(vector<vector<T>> &A, vector<vector<T>> &B){
    vector<vector<T>> ret;
    for (int i = 0; i < (int)A.size(); i++){
        vector<T> row;
        for (int j = 0; j < (int)B[0].size(); j++){
            T ele = 0;
            for (int k = 0; k < (int)A[0].size(); k++){
                ele += A[i][k] * B[k][j];
            }
            row.push_back(ele);
        }
        ret.push_back(row);
    }
    return ret;
}

template<typename T> vector<vector<T>> multidot(vector<vector<T>> &A, ll &N){
    vector<vector<T>> ret((int)A.size(), vector<T>((int)A.size(), 0));
    for (int i = 0; i < (int)A.size(); i++) ret[i][i] = 1;
    while (N > 0){
        if (N & 1) ret = dot(ret, A);
        A = dot(A, A);
        N >>= 1;
    }
    return ret;
}
