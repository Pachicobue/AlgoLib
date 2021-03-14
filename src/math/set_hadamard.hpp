#pragma once
#include <vector>
#include "../misc/bit_ops.hpp"
template<typename T>
std::vector<T> set_hadamard(const std::vector<T>& xs, const bool rev = false)
{
    const int N = ceil2(xs.size());
    std::vector<T> ys(N);
    for (int i = 0; i < (int)xs.size(); i++) { ys[i] = xs[i]; }
    for (int i = 1; i < N; i <<= 1) {
        for (int j = 0; j < N; j++) {
            if ((j & i) == 0) {
                const T x = ys[j], y = ys[j | i];
                ys[j] = x + y, ys[j | i] = x - y;
            }
        }
    }
    if (rev) {
        const T iN = T{1} / N;
        for (auto& y : ys) { y *= iN; }
    }
    return ys;
}
