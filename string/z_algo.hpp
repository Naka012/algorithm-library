// 出典: https://snuke.hatenablog.com/entry/2014/12/03/214243

vector<int> z_algo(string &S){
    int N = (int)S.size();
    vector<int> Z(N);
    Z[0] = N;
    int i = 1, j = 0;
    while(i < N){
        while(i + j < N && S[j] == S[i + j]) j++;
        Z[i] = j;
        if(j == 0){
            i++;
            continue;
        }
        int k = 1;
        while(k < j && k + Z[k] < j){
            Z[i + k] = Z[k];
            k++;
        }
        i += k;
        j -= k;
    }
    return Z;
}
