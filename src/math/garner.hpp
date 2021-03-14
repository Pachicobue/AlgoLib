#pragma once
#include <vector>
#include "mod_pow.hpp"
template<typename T>
std::vector<T> garner(const std::vector<T>& xs, const std::vector<T>& ms)
{
    const int N = (int)xs.size();
    std::vector<T> as(N);
    for (int i = 0; i < N; i++) {
        const T xi = xs[i], mod = ms[i];
        T p = 1, sum = 0;
        for (int j = 0; j < i; j++) {
            const T xj = xs[j];
            (sum += p * as[j] % mod) %= mod;
            (p *= (xi + mod - xj)) %= mod;
        }
        const T res = (xi + mod - sum) % mod;
        as[i]       = res * mod_pow(p, mod - 2, mod) % mod;
    }
    return as;
}
