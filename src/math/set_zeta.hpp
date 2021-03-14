#pragma once
#ifndef WITHOUT_STANDARD_LIBRARY
#    include <vector>
#endif
#include "../misc/bit_ops.hpp"
template<typename T>
std::vector<T> set_zeta(const std::vector<T>& xs, const bool subset)
{
    const int N = ceil2(xs.size());
    std::vector<T> ys(N);
    for (int i = 0; i < (int)xs.size(); i++) { ys[i] = xs[i]; }
    for (int i = 1; i < N; i <<= 1) {
        for (int j = 0; j < N; j++) {
            if ((j & i) == 0) { (subset ? ys[j | i] : ys[j]) += (subset ? ys[j] : ys[j | i]); }
        }
    }
    return ys;
}
