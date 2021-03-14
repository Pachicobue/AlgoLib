#pragma once
#include "berlekamp_massey.hpp"
#include "fps_div_nth.hpp"
template<typename mint>
mint nth_term(const std::vector<mint>& as, const ll N)
{
    const fps g{berlekamp_massey(as)};
    const int L  = g.size();
    const auto f = fps<mint>{as}.mult(g, L - 1);
    return div_nth(f, g, N);
}
