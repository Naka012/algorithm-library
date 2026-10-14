// https://github.com/Naka012/algorithm-library/blob/main/math_else/itertools.hpp

//重複組み合わせ [0, N) の数 選ぶ個数はlen(A)に依存

bool next_homogeneous_product(int N, vector<int> &A){
    int k = (int)A.size();
    rep(i, k - 1) if (A[i] < A[i + 1]){
        A[i]++;
        rep(j, i) A[j] = 0;
        return true;
    }
    if (A[k - 1] < N - 1){
        A[k - 1]++;
        rep(i, k - 1) A[i] = 0;
        return true;
    }
    return false;
}

//組み合わせ [0, N) の数 選ぶ個数はlen(A)に依存

bool next_combination(int N, vector<int> &P){
    int k = (int)P.size();
    rep(i, k - 1) if (P[i] + 1 < P[i + 1]){
        P[i]++;
        rep(j, i) P[j] = j;
        return true;
    }
    if (P[k - 1] < N - 1){
        P[k - 1]++;
        rep(i, k - 1) P[i] = i;
        return true;
    }
    return false;
}

// 総和が sm(P), 長さが len(P) の分割 小さい順
bool next_partition_function(vector<int>& P){
    if ((int)P.size() == 1) return false;
    int sm = P.back();
    for (int i = (int)P.size() - 2; i >= 0; i--){
        if ((P[i] + 1) * ((int)P.size() - 1 - i) < sm){
            P[i]++;
            for (ll j = i + 1; j < (int)P.size(); j++) P[j] = P[i];
            sm -= P[i] * ((int)P.size() - 1 - i);
            sm--;
            P.back() += sm;
            return true;
        }else sm += P[i];
    }
    return false;
}
