#pragma once
#include <algorithm>
#include <vector>
template<typename T>
std::vector<T> berlekamp_massey(const std::vector<T>& A)
{
    const int N = (int)A.size();
    std::vector<T> B{1}, C{1};
    T b = 1;
    for (int j = 1; j <= N; j++) {
        int m = (int)B.size(), l = (int)C.size();
        T d = 0;
        for (int i = 0; i < l; i++) { d += A[j - l + i] * C[i]; }
        B.push_back(0), m++;
        if (d == 0) { continue; }
        const T c = -d / b;
        if (l < m) {
            auto temp = C;
            C.insert(C.begin(), m - l, 0);
            for (int i = 0; i < m; i++) { C[m - 1 - i] += c * B[m - 1 - i]; }
            B = temp, b = d;
        } else {
            for (int i = 0; i < m; i++) { C[l - 1 - i] += c * B[m - 1 - i]; }
        }
    }
    return std::reverse(C.begin(), C.end()), C;
}
