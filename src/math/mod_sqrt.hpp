#pragma once
#include "../misc/types.hpp"

template<typename mint>
mint modsqrt(const mint& A)
{
    const ull P = mint::mod;
    if (A == 0) { return 0; }
    if (P == 2) { return 1; }
    const ull h = (P - 1) >> 1;
    if (A.pow(h)() != 1) { return 0; }

    ull q = P - 1, Q = 0;
    while ((q & 1) == 0) { q >>= 1, Q++; }

    mint Eraser = 1;
    for (mint Z = 2;; Z += 1) {
        if (Z.pow(h) != 1) {
            Eraser = Z.pow(q);
            break;
        }
    }
    mint Error = A.pow(q), X = A.pow((q + 1) / 2);
    while (Error() != 1) {
        ull l       = 0;
        mint pError = Error;
        for (ull i = 0; i < Q; i++, pError *= pError) {
            if (pError() == 1) {
                l = Q - i;
                break;
            }
        }
        mint pEraser = Eraser;
        for (ull i = 0; i < l - 1; i++, pEraser *= pEraser) {}
        X *= pEraser, Error *= (pEraser * pEraser);
    }
    return X;
}
