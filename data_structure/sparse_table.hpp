// https://github.com/Naka012/algorithm-library/blob/main/data_structure/sparse_table.hpp

/*
sparse_table
(min max lcm gcd)
sparse_table<T, op, e> sp(int n)  -> sp.build(A)
sparse_table<T, op, e> sp(A)

型 T
二項演算 T op(T a, T b)
単位元 T e()

長さnの配列に対し、
build O(n log n)
prod O(1)

*/

template<class T, T (*op)(T, T), T (*e)()> struct sparse_table {
    public : 
        sparse_table(int n) : _n(n) {
            bits = 0;
            var = n;
            for (bits; var != 0; bits++) var >>= 1;
            table = vector<vector<T>>(n, vector<T>(bits + 1, e()));
        }

        sparse_table(const vector<T> &A) : sparse_table((int)A.size()) {
            build(A);
        }

        void build(const vector<T> &A) {
            assert((int)A.size() <= _n);
            for (int i = 0; i < _n; i++) table[i][0] = A[i];
            for (int k = 1; k < bits; k++){
                for (int i = 0; i < _n - (1 << k) + 1; i++){
                    table[i][k] = op(table[i][k - 1], table[i + (1 << (k - 1))][k - 1]);
                }
            }
            
        }

        T prod(int l, int r){
            assert(0 <= l && l <= _n);
            assert(0 <= r && r <= _n);
            if (l == r) return e();
            int l2 = (int)log2(r - l);
            return op(table[l][l2], table[r - (1 << l2)][l2]);
        }

    private : 
        int _n, bits, var;
        vector<vector<T>> table;
};
