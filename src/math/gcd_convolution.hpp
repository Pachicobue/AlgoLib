#pragma once
#include "divisors_moebius.hpp"
#include "divisors_zeta.hpp"
template<typename T>
std::vector<T> gcd_convolute(const std::vector<T>& f, const std::vector<T>& g)
{
    const int N = (int)std::min(f.size(), g.size());
    auto F = divisors_zeta(f, false), G = divisors_zeta(g, false);
    F.resize(N), G.resize(N);
    for (int i = 0; i < N; i++) { F[i] *= G[i]; }
    return divisors_moebius(F, false);
}
