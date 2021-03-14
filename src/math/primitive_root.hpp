#pragma once
#include "prime_factors.hpp"
template<typename mint>
mint primitive_root()
{
    const auto p = mint::mod;
    if (p == 2) { return 1; }
    const auto fs = prime_factors(p - 1);
    for (mint g = 2;; g += 1) {
        bool ok = true;
        for (const auto& [p, n] : fs) {
            const auto per = (p - 1) / p;
            if (g.pow(per)() == 1) {
                ok = false;
                break;
            }
        }
        if (ok) { return g; }
    }
    return 0;
}
