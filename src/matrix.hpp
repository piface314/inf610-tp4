#ifndef MATRIX_H
#define MATRIX_H


#include <ostream>

#define PRINT_M(A,M,N) {std::cout << "\u23A1"; \
    for (size_t i = 0; i < M; ++i) { \
        std::cout << (i ? " " : "") << " "; \
        for (size_t j = 0; j < N; ++j) \
            std::cout << A[i][j] << " "; \
        if (i + 1 == M) std::cout << "\u23A6"; \
        std::cout << "\n"; \
    }}

template <typename T>
struct Matrix {
    T *a;
    int m, n;

    Matrix(int m, int n) : m(m), n(n) {
        a = new T[m*n];
    }

    ~Matrix() { delete [] a; }

    T &operator()(int i, int j) {
        return a[i*n + j];
    }

    friend std::ostream& operator<<(std::ostream& os, Matrix<T> &matrix) {
        os << "\u23A1"; \
        for (int i = 0; i < matrix.m; ++i) { \
            os << (i ? " " : "") << " "; \
            for (int j = 0; j < matrix.n; ++j) \
                os << matrix(i,j) << " "; \
            if (i + 1 == matrix.m) os << "\u23A6"; \
            os << "\n"; \
        }
        return os;
    }
};



#endif