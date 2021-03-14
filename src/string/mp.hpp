#pragma once
#include <string>
#include <vector>
template<typename InIt>
std::vector<int> mp(const InIt first, const InIt last)
{
    const int sz = std::distance(first, last);
    std::vector<int> A(sz + 1, -1);
    for (int i = 0, j = -1; i < sz; i++) {
        while (j != -1 and *(std::next(first, i)) != *(std::next(first, j))) { j = A[j]; }
        j = (j == -1 ? 0 : j + 1), A[i + 1] = j;
    }
    return A;
}
