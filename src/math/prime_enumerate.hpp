#pragma once
#include "../misc/types.hpp"
#include "factor_table.hpp"
std::vector<u32> prime_enumerate(const u32 sup)
{
    const auto ftable = factor_table(sup);
    std::vector<u32> ps;
    for (u32 p = 2; p < sup; p++) {
        if (ftable[p] == p) { ps.push_back(p); }
    }
    return ps;
}
