#pragma once
#include "and_convolution.hpp"
template<typename T>
std::vector<T> or_convolute(std::vector<T> f, std::vector<T> g)
{
    const int N = ceil2(std::max(f.size(), g.size()));
    f.resize(N), g.resize(N);
    auto F = set_zeta(f, true), G = set_zeta(g, true);
    for (int i = 0; i < N; i++) { F[i] *= G[i]; }
    return set_moebius(F, true);
}
