#pragma once
#include "matrix.hpp"
template<typename T>
matrix<T> gauss_jordan(matrix<T> mat)
{
    for (int r = 0, c = 0; c < mat.column; c++) {
        if (r == mat.row) { break; }
        int piv = r;
        for (; piv < mat.row and mat[piv][c] == static_cast<T>(0); piv++) {}
        if (piv == mat.row) { continue; }
        for (int j = c + 1; j < mat.column; j++) { mat[piv][j] /= mat[piv][c]; }
        std::swap(mat[piv], mat[r]), mat[r][c] = 1;
        for (int j = 0; j < mat.row; j++) {
            if (j == r) { continue; }
            for (int k = c + 1; k < mat.column; k++) { mat[j][k] -= mat[r][k] * mat[j][c]; }
            mat[j][c] = 0;
        }
        r++;
    }
    return mat;
}
