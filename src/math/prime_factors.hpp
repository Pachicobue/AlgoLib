#pragma once
#include <map>
#include <numeric>
#include "../misc/random.hpp"
#include "../misc/types.hpp"
#include "is_prime.hpp"

template<typename mint>
u64 pollard_rho(const u64 n)
{
    if (n % 2 == 0) { return 2; }
    if (is_prime(n)) { return n; }
    mint c;
    auto f = [&](const mint x) { return x * x + c; };
    while (true) {
        mint x, y, ys, q = 1;
        y = rng.val<u64>(0, n - 2) + 2, c = rng.val<u64>(0, n - 2) + 2;
        u64 d            = 1;
        constexpr u32 dk = 128;
        for (u32 r = 1; d == 1; r <<= 1) {
            x = y;
            for (u32 i = 0; i < r; i++) { y = f(y); }
            for (u32 k = 0; k < r and d == 1; k += dk) {
                ys = y;
                for (u32 i = 0; i < dk and i < r - k; i++) { q *= x - (y = f(y)); }
                d = std::gcd((u64)q.get(), n);
            }
        }
        if (d == n) {
            do {
                d = std::gcd(u64((x - (ys = f(ys))).get()), n);
            } while (d == 1);
        }
        if (d != n) { return d; }
    }
    return n;
}

std::map<u64, int> prime_factors(const u64 n)
{
    static moddinfo info;
    static moddinfo64 info64;
    using mint   = moddint<info>;
    using mint64 = moddint64<info64>;
    std::map<u64, int> ans;
    auto fac = [&](auto self, ull x) -> void {
        while ((x & 1) == 0) { x >>= 1, ans[2]++; }
        if (x == 1) { return; }
        u64 p;
        if (x < (1ULL << 30)) {
            info.set_mod(x);
            p = pollard_rho<mint>(x);
        } else {
            info64.set_mod(x);
            p = pollard_rho<mint64>(x);
        }
        if (p == x) { return ans[p]++, void(0); }
        self(self, p), self(self, x / p);
    };
    return fac(fac, n), ans;
}

std::vector<u64> divisors(const u64 n)
{
    const auto fs = prime_factors(n);
    std::vector<u64> ds{1};
    for (const auto& [p, e] : fs) {
        u64 pe       = p;
        const u32 dn = ds.size();
        for (i32 i = 0; i < e; i++, pe *= p) {
            for (u32 j = 0; j < dn; j++) { ds.push_back(ds[j] * pe); }
        }
    }
    return ds;
}
