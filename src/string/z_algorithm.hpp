#pragma once
#include <string>
#include <vector>
template<typename InIt>
std::vector<int> z_algorithm(const InIt first, const InIt last)
{
    const int sz = std::distance(first, last);
    std::vector<int> ans(sz, -1);
    for (int i = 1, j = 0; i < sz;) {
        while (i + j < sz and *std::next(first, j) == *std::next(first, i + j)) { j++; }
        ans[i] = j;
        if (j == 0) {
            ++i;
            continue;
        }
        int k = 1;
        while (i + k < sz and k + ans[k] < j) { ans[i + k] = ans[k], k++; }
        i += k, j -= k;
    }
    return ans[0] = sz, ans;
}
