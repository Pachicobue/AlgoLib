#pragma once
#include "set_hadamard.hpp"
template<typename T>
std::vector<T> xor_convolute(std::vector<T> f, std::vector<T> g)
{
    const int N = ceil2(std::max(f.size(), g.size()));
    f.resize(N), g.resize(N);
    auto F = set_hadamard(f, false), G = set_hadamard(g, false);
    for (int i = 0; i < N; i++) { F[i] *= G[i]; }
    return set_hadamard(F, true);
}
