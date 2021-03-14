#pragma once
#include <cassert>
#include <cmath>
#include <vector>
#include "../math/complex.hpp"
#include "../math/modint.hpp"
#include "../misc/bit_ops.hpp"
#include "../misc/constants.hpp"
template<typename R>
class fft
{
private:
    static constexpr R pi  = pi_v<R>;
    static constexpr int D = 30;
    static constexpr int B = 14;
    static void trans(std::vector<complex<R>>& as, const int lg, const bool rev)
    {
        const int N = as.size();
        static std::vector<complex<R>> root[D];
        if (root[lg].empty()) {
            root[lg].resize(N);
            for (int i = 0; i < N; i++) {
                const R theta = pi * R(2 * i) / R(N);
                root[lg][i]   = complex<R>(std::cos(theta), std::sin(theta));
            }
        }
        std::vector<complex<R>> tmp(N);
        for (int w = (N >> 1); w > 0; w >>= 1) {
            for (int y = 0; y < (N >> 1); y += w) {
                const complex<R> r = rev ? root[lg][y].conj() : root[lg][y];
                for (int x = 0; x < w; x++) {
                    const auto u = as[y << 1 | x], v = as[y << 1 | x | w] * r;
                    tmp[y | x] = u + v, tmp[y | x | (N >> 1)] = u - v;
                }
            }
            std::swap(tmp, as);
        }
    }

public:
    fft() = delete;
    template<typename T, typename V = T>
    static std::vector<V> convolute(const std::vector<T>& as, const std::vector<T>& bs)
    {
        const int need = as.size() + bs.size() - 1, lg = clog(need), sz = 1UL << lg;
        std::vector<complex<R>> xs(sz), ys(sz);
        for (int i = 0; i < as.size(); i++) { xs[i] = {(R)as[i], (R)0}; }
        for (int i = 0; i < bs.size(); i++) { ys[i] = {(R)bs[i], (R)0}; }
        trans(xs, lg, false), trans(ys, lg, false);
        for (int i = 0; i < sz; i++) { xs[i] *= ys[i]; }
        trans(xs, lg, true);
        std::vector<T> ans(need);
        for (int i = 0; i < need; i++) { ans[i] = (T)std::round(xs[i].real / (R)sz); }
        return ans;
    }
};
