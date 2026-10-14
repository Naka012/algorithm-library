// https://github.com/Naka012/algorithm-library/blob/main/convolutions/gcd_convolution.hpp

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

template<class T> vector<T> multiple_zeta(vector<T> A, vector<bool> &is_prime){
    int N = (int)A.size() - 1;
    for (int p = 0; p <= N; p++){
        if (is_prime[p]){
            for (int k = N / p; k > 0; --k){
                A[k] += A[k * p];
            }
        }
    }
    return A;
}

template<class T> vector<T> multiple_mebious(vector<T> A, vector<bool> &is_prime){
    int N = (int)A.size() - 1;
    for (int p = 0; p <= N; p++){
        if (is_prime[p]){
            for (int k = 1; k * p <= N; ++k){
                A[k] -= A[k * p];
            }
        }
    }
    return A;
}

template<class T> vector<T> gcd_convolution(vector<T> &A, vector<T> &B){
    int length = max((int)A.size(), (int)B.size());
    vector<bool> is_prime = eratosthenes(length);
    A.resize(length); B.resize(length);
    vector<T> zetaA = multiple_zeta<T>(A, is_prime), zetaB = multiple_zeta<T>(B, is_prime);
    vector<T> cross(length);
    for (int i = 0; i < length; i++) cross[i] = zetaA[i] * zetaB[i];
    vector<T> ret = multiple_mebious<T>(cross, is_prime);
    return ret;
}
