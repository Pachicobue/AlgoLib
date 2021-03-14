#pragma once
#include "../misc/types.hpp"
#include "prime_enumerate.hpp"
template<typename T>
std::vector<T> divisors_zeta(const std::vector<T>& xs, const bool subset)
{
    const int N = (int)xs.size();
    auto ys     = xs;
    for (const i32 p : prime_enumerate(N)) {
        if (subset) {
            for (i32 i = 1; i * p < N; i++) { ys[i * p] += ys[i]; }
        } else {
            for (i32 i = (N - 1) / p; i >= 1; i--) { ys[i] += ys[i * p]; }
        }
    }
    return ys;
}
