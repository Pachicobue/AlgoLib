#pragma once
#include "set_moebius.hpp"
#include "set_zeta.hpp"
template<typename T>
std::vector<T> and_convolute(std::vector<T> f, std::vector<T> g)
{
    const int N = ceil2(std::max(f.size(), g.size()));
    f.resize(N), g.resize(N);
    auto F = set_zeta(f, false), G = set_zeta(g, false);
    for (int i = 0; i < N; i++) { F[i] *= G[i]; }
    return set_moebius(F, false);
}
