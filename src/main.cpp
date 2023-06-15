#include <iostream>
#include <fstream>
#include <cmath>
#include "matrix.hpp"


Matrix<int> *read(std::string fp);
Matrix<int> *solve_latin_square(Matrix <int> &ls);
Matrix<int> *latin_square_to_sudoku(Matrix<int> &ls);
Matrix<int> *solve_sudoku(Matrix<int> &sd);
Matrix<int> *sudoku_to_latin_square(Matrix<int> &sd);
bool         check_latin_square(Matrix<int> &ls);

int main(int argc, char const *argv[]) {
    if (argc <= 1) {
        std::cout << "Usage:\n\t$ " << argv[0] << "<input>\n";
        return 1;
    }
    Matrix<int> *ls = read(argv[1]);
    std::cout << *ls << "\n";
    Matrix<int> *ls_solution = solve_latin_square(*ls);
    if (ls_solution != NULL)
        std::cout << *ls_solution << "\n";
    else
        std::cout << "NO SOLUTION\n";
    return 0;
}

Matrix<int> *read(std::string fp) {
    std::ifstream f_in(fp);
    int n;
    f_in >> n;
    Matrix<int> *matrix = new Matrix<int>(n, n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            f_in >> (*matrix)(i, j);
    return matrix;
}

Matrix<int> *solve_latin_square(Matrix <int> &ls) {
    // f_1 : I_LS -> I_SD, transforma instancia de LS em instancia de SD
    Matrix<int> *sd = latin_square_to_sudoku(ls);

    // A_SD : I_SD -> S_SD, soluciona problema SD
    Matrix<int> *sd_solution = solve_sudoku(*sd);

    // f_2 : S_SD -> S_LS, transforma solucao de SD em solucao de LS
    Matrix<int> *ls_solution = sudoku_to_latin_square(*sd_solution);

    // verifica solucao de LS
    if (check_latin_square(*ls_solution))
        return ls_solution;
    else
        return NULL;
}

Matrix<int> *latin_square_to_sudoku(Matrix<int> &ls) {
    int n = ls.n;
    int n2 = n * n;
    Matrix<int> *sd = new Matrix<int>(n2, n2);
    for (int i = 0; i < n2; ++i)
        for (int j = 0; j < n2; ++j)
            if (i / n == 0 && j % n == 0)
                (*sd)(i, j) = (ls(i, j/n) < 0) ? -1 : ls(i, j/n) * n;
            else
                (*sd)(i, j) = ((i % n) * n + i / n + j) % n2;
    return sd;
}

bool check_sudoku(Matrix<int> &sd, int i, int j) {
    int v = sd(i, j);
    for (int k = 0; k < sd.n; ++k) {
        if (k != j && sd(i, k) == v) return false;
        if (k != i && sd(k, j) == v) return false;
    }
    int n = (int)std::sqrt(sd.n);
    int i0 = i - (i % n), j0 = j - (j % n);
    for (int i_ = i0; i_ < i0 + n; ++i_)
        for (int j_ = j0; j_ < j0 + n; ++j_)
            if ((i_ != i || j_ != j) && sd(i_, j_) == v)
                return false;
    return true;
}

bool solve_sudoku(Matrix<int> &sd, int i, int j) {
    if (i == sd.n)
        return true;
    int i_next, j_next;
    if (j == sd.n - 1)
        i_next = i+1, j_next = 0;
    else
        i_next = i,   j_next = j+1;
    if (sd(i, j) >= 0)
        return solve_sudoku(sd, i_next, j_next);
    for (int k = 0; k < sd.n; ++k) {
        sd(i, j) = k;
        if (check_sudoku(sd, i, j) && solve_sudoku(sd, i_next, j_next))
            return true;
        sd(i, j) = -1;
    }
    return false;
}

Matrix<int> *solve_sudoku(Matrix<int> &sd) {
    Matrix<int> *sd_solution = new Matrix<int>(sd.n, sd.n);
    for (int i = 0; i < sd.n; ++i)
        for (int j = 0; j < sd.n; ++j)
            (*sd_solution)(i, j) = sd(i, j);
    solve_sudoku(*sd_solution, 0, 0);
    return sd_solution;
}

Matrix<int> *sudoku_to_latin_square(Matrix<int> &sd) {
    int n = (int)std::sqrt(sd.n);
    Matrix<int> *ls = new Matrix<int>(n, n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            (*ls)(i, j) = sd(i, j*n) / n;
    return ls;
}

bool check_latin_square(Matrix<int> &ls) {
    int n = ls.n;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            int v = ls(i, j);
            if (v < 0 || v >= n)
                return false;
            for (int k = 0; k < n; ++k) {
                if (k != j && ls(i, k) == v)
                    return false;
                if (k != i && ls(k, j) == v)
                    return false;
            }
        }
    return true;
}
