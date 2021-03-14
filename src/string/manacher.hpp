#pragma once
#include <string>
#include <vector>
template<typename InIt>
std::vector<int> manacher(const InIt first, const InIt last)
{
    const int sz = std::distance(first, last);
    std::vector<int> ans(sz);
    for (int i = 0, k = 1, j = 0; i < sz; i += k, j -= k, k = 1) {
        while (i >= j and i + j < sz and *std::next(first, i - j) == *std::next(first, i + j)) { ++j; }
        ans[i] = j;
        while (i >= k and i + k < sz and k + ans[i - k] < j) { ans[i + k] = ans[i - k], ++k; }
    }
    return ans;
}
