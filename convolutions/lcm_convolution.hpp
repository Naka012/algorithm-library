vector<bool> eratosthenes(int t){
    vector<bool> is_prime(t + 1, true);
    is_prime[0] = false; is_prime[1] = false;
    for (int i = 0; i <= t; i++){
        if (is_prime[i]){
            for (int q = i * 2; q <= t; q += i){
                is_prime[q] = false;
            }
        }
    }
    return is_prime;
}

template<class T> vector<T> diviser_zeta(vector<T> A, vector<bool> &is_prime){
    int N = (int)A.size() - 1;
    for (int p = 0; p <= N; p++){
        if (is_prime[p]){
            for (int k = 1; k * p <= N; ++k){
                A[k * p] += A[k];
            }
        }
    }
    return A;
}

template<class T> vector<T> diviser_mebious(vector<T> A, vector<bool> &is_prime){
    int N = (int)A.size() - 1;
    for (int p = 0; p <= N; p++){
        if (is_prime[p]){
            for (int k = N / p; k > 0; --k){
                A[k * p] -= A[k];
            }
        }
    }
    return A;
}

template<class T> vector<T> lcm_convolution(vector<T> &A, vector<T> &B){
    int length = max((int)A.size(), (int)B.size());
    vector<bool> is_prime = eratosthenes(length);
    A.resize(length); B.resize(length);
    vector<T> zetaA = diviser_zeta<T>(A, is_prime), zetaB = diviser_zeta<T>(B, is_prime);
    vector<T> cross(length);
    for (int i = 0; i < length; i++) cross[i] = zetaA[i] * zetaB[i];
    vector<T> ret = diviser_mebious<T>(cross, is_prime);
    return ret;
}
