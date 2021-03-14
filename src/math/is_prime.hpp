#pragma once
#include <vector>
#include "../misc/types.hpp"
#include "moddint.hpp"
#include "moddint64.hpp"

template<typename mint>
inline bool miller_rabin(const u64 n, const std::vector<u64>& as)
{
    auto d = n - 1;
    for (; (d & 1) == 0; d >>= 1) {}
    for (const u64 a : as) {
        if (n <= a) { break; }
        auto s = d;
        mint x = mint(a).pow(s);
        while (x.get() != 1 and x.get() != n - 1 and s != n - 1) { x *= x, s <<= 1; }
        if (x.get() != n - 1 and s % 2 == 0) { return false; }
    }
    return true;
}
inline bool is_prime(const u64 n)
{
    static moddinfo info;
    static moddinfo64 info64;
    using mint   = moddint<info>;
    using mint64 = moddint64<info64>;
    if (n == 1) { return false; }
    if ((n & 1) == 0) { return n == 2; }
    if (n < (1ULL << 30)) {
        info.set_mod(n);
        return miller_rabin<mint>(n, {2, 7, 61});
    } else {
        info64.set_mod(n);
        return miller_rabin<mint64>(n, {2, 325, 9375, 28178, 450775, 9780504});
    }
}
