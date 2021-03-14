#pragma once
#include "bit_matrix.hpp"
template<int column>
bit_matrix<column> gauss_jordan(bit_matrix<column> mat)
{
    for (int r = 0, ci = 0; ci < column; ci++) {
        const int c = column - ci - 1;
        if (r == mat.row) { break; }
        int piv = r;
        for (; piv < mat.row and not mat[piv][c]; piv++) {}
        if (piv == mat.row) { continue; }
        std::swap(mat[piv], mat[r]);
        for (int j = 0; j < mat.row; j++) {
            if (j == r) { continue; }
            if (mat[j][c]) { mat[j] ^= mat[r]; }
        }
        r++;
    }
    return mat;
}
