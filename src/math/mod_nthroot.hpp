#pragma once
#include <cmath>

#include "../data_structure/hashmap.hpp"
#include "../misc/types.hpp"
#include "extgcd.hpp"
#include "prime_factors.hpp"

template<typename mint>
mint mod_nthroot(mint A, ull k)
{
    const ull P = mint::mod;
    if (A == 0) { return 0; }
    if (k == 0) { return A; }
    const ull g = std::gcd(P - 1, k);
    if (A.pow((P - 1) / g)() != 1) { return 0; }
    A = A.pow(inverse<ULL>(k / g, (P - 1) / g));

    if (g == 1) { return A; }
    const auto fs = prime_factors(g);
    for (const auto& [p, e] : fs) {
        ull pe = 1;
        for (int i = 0; i < e; i++) { pe *= p; }
        ull q = P - 1, Q = 0;
        while (q % p == 0) { q /= p, Q++; }
        const ull y = pe - inverse<ULL>(q, pe), z = ((ULL)y * q + 1) / (ULL)pe;
        mint X = A.pow(z);
        if ((int)Q == e) {
            A = X;
            continue;
        }

        mint Eraser = 1;
        const ull h = (P - 1) / p;
        for (mint Z = 2;; Z += 1) {
            if (Z.pow(h) != 1) {
                Eraser = Z.pow(q);
                break;
            }
        }
        mint Error = A.pow((ULL)y * q);

        mint pEraser = Eraser;
        for (ull i = 0; i < Q - 1; i++) { pEraser = pEraser.pow(p); }
        const mint ipEraser = pEraser.inv();

        hashmap<ull, ull> memo;
        {
            const ull M = std::max(1ULL, (ull)(std::sqrt(p) * std::sqrt(Q - e))), B = std::max(1ULL, ((ull)p - 1) / M);
            const mint ppEraser = pEraser.pow(B);
            mint prod           = 1;
            for (ull i = 0; i < p; i += B, prod *= ppEraser) { memo[prod()] = i; }
        }

        while (Error() != 1) {
            ull l       = 0;
            mint pError = Error;
            for (ull i = 0; i < Q; i++) {
                const auto npError = pError.pow(p);
                if (npError == 1) {
                    l = Q - (i + 1);
                    break;
                }
                pError = npError;
            }

            ull c = -1;
            {
                mint small = pError.inv();
                for (ull j = 0;; j++, small *= ipEraser) {
                    if (memo.count(small())) {
                        const ull i = memo[small()];
                        c           = i + j;
                        break;
                    }
                }
            }
            auto pEraser2 = Eraser.pow(c);
            for (ull i = 0; i < l - e; i++) { pEraser2 = pEraser2.pow(p); }
            X *= pEraser2, Error *= pEraser2.pow(pe);
        }
        A = X;
    }
    return A;
}
