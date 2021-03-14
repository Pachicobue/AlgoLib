#pragma once
#include <numeric>
#include "fps.hpp"
template<typename mint>
fps<mint> lagrange_interpolate(const std::vector<mint> ys)
{
    const int N = ys.size();
    std::vector<mint> fs(N + 1);
    std::iota(fs.begin(), fs.end(), 0);
    for (int i = 2; i <= N; i++) { fs[i] = fs[i - 1] * i; }

    std::vector<mint> as(N + 1);
    for (int i = 0; i <= N; i++) {
        mint res = fs[i];
        for (int j = 0; j < i; j++) { res -= as[i] * mint::fact(i) * mint::ifact(i - j); }
        as[i] = res * mint::ifact(i);
    }
    fps<mint> ans, g{1};
    for (int i = 0; i <= N; i++) {
        ans += as[i] * g;
        g *= fps<mint>{1, -i};
    }
    return ans;
}
