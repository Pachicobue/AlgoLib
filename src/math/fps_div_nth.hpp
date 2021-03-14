#pragma once
#include "fps.hpp"
template<typename mint>
mint div_nth(fps<mint> f, fps<mint> g, ll N)
{
    if (f.size() == 0) { return 0; }
    const int n = g.size();
    int mi      = 0;
    mint a;
    for (int i = 0; i < n; i++) {
        if (g[i]() != 0) {
            mi = i, a = g[i];
            break;
        }
    }
    g >>= mi;
    const mint ia = a.inv();
    for (auto& c : f) { c *= ia; }
    for (auto& c : g) { c *= ia; }
    fps p = f.quot(g);
    f -= g * p, N += mi;
    if (N < 0) { return 0; }
    const mint offset = p.at(N);
    for (; N > 0; N >>= 1) {
        fps mg = g;
        for (int i = 1; i < n; i += 2) { mg[i] = -mg[i]; }
        const auto fmg = f * mg;
        const auto gmg = g * mg;
        f.clear(), g.clear();
        for (int i = 0; i < gmg.size(); i += 2) { g[i >> 1] = gmg[i]; }
        if (N % 2 == 0) {
            for (int i = 0; i < fmg.size(); i += 2) { f[i >> 1] = fmg[i]; }
        } else {
            for (int i = 1; i < fmg.size(); i += 2) { f[i >> 1] = fmg[i]; }
        }
    }
    return offset + f.at(0);
}
