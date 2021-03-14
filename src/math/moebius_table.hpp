#pragma once
#include "factor_table.hpp"
std::vector<int> moebius_table(const int sup)
{
    const auto f_table = factor_table(sup);
    auto moebius       = [&](int n) {
        int ans = 1;
        for (int prev = 1; n > 1; prev = f_table[n], n /= prev, ans = -ans) {
            if (prev == f_table[n]) { return 0; }
        }
        return ans;
    };
    std::vector<int> ans(sup, 0);
    for (int i = 1; i < sup; i++) { ans[i] = moebius(i); }
    return ans;
}
