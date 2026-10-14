// https://github.com/Naka012/algorithm-library/blob/main/convolutions/and_convolution.hpp

template<class T> vector<T> and_zeta(vector<T> A){
    int N = 0;
    while (1 << N < (int)A.size()) N++;
    for (int i = 0; i < N; i++){
        for (int S = 0; S < 1 << N; S++){
            if (~S & (1 << i)){
                A[S] += A[S ^ (1 << i)];
            }
        }
    }
    return A;
}

template<class T> vector<T> and_mebious(vector<T> A){
    int N = 0;
    while (1 << N < (int)A.size()) N++;
    for (int i = 0; i < N; i++){
        for (int S = 0; S < 1 << N; S++){
            if (~S & (1 << i)){
                A[S] -= A[S ^ (1 << i)];
            }
        }
    }
    return A;
}

template<class T> vector<T> and_convolution(vector<T> &A, vector<T> &B){
    int length = 0;
    while (1 << length < (int)A.size()) length++;
    while (1 << length < (int)B.size()) length++;
    A.resize(1 << length);
    B.resize(1 << length);
    vector<T> zetaA = and_zeta(A), zetaB = and_zeta(B);
    for (int i = 0; i < 1 << length; i++) zetaA[i] *= zetaB[i];
    vector<T> ret = and_mebious(zetaA);
    return ret;
}
