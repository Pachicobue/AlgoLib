#pragma once
#include <numeric>
#include <vector>
#include "../misc/types.hpp"
std::vector<u32> factor_table(const u32 sup)
{
    std::vector<u32> fact(sup);
    std::iota(fact.begin(), fact.end(), 0);
    for (u32 i = 2; i < sup; i++) {
        if (fact[i] != i) { continue; }
        for (u32 j = i + i; j < sup; j += i) { fact[j] = i; }
    }
    return fact;
}
