vector<int> eratosthenes(int t){
    vector<int> is_prime(t + 1, 1);
    is_prime[0] = 0; is_prime[1] = 0;
    for (int i = 0; i <= t; i++){
        if (is_prime[i]){
            for (int q = i * 2; q <= t; q += i){
                is_prime[q] = 0;
            }
        }
    }
    return is_prime;
}
