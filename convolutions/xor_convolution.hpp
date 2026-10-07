template<class T> vector<T> Hadamard_Transform(vector<T> &A){
    int L = (int)A.size();
    T h = 1;
    rep(_, L){
        for (int i = 0; i < L; i += h * 2) for (ll j = i; j < i + h; j++){
            A[j] = A[j] + A[j + h];
            A[j + h] = A[j] - A[j + h];
        }
        h *= 2;
    }
}

template<class T> vector<T> xor_convolution(vector<T> &A, vector<T> &B){
    int N = max((int)A.size(), (int)B.size()), bit = 0;
    while (N > 0){
        N >>= 1;
        bit++;
    }
    A.resize(1 << bit, 0);
    B.resize(1 << bit, 0);
    Hadamard_Transform(A);
    Hadamard_Transform(B);
    rep(i, 1 << bit) A[i] *= B[i];
    Hadamard_Transform(A);
    rep(i, 1 << bit) A[i] >>= bit;
    return A;
}
