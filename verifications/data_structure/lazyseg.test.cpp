#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"
#include "data_structure/lazyseg.hpp"
#include "math/modint.hpp"
#include "misc/fastio/printer.hpp"
#include "misc/fastio/scanner.hpp"

int main()
{
    using mint = modint_998244353;
    using Func = std::pair<mint, mint>;
    struct MergeMonoid
    {
        using T = std::pair<mint, int>;
        static T e() { return {0, 0}; }
        T operator()(const T& x1, const T& x2) const { return {x1.first + x2.first, x1.second + x2.second}; }
    };
    struct OpMonoid
    {
        using F = Func;
        static F id() { return F{1, 0}; }
        F operator()(const F& f1, const F& f2) const { return F{f1.first * f2.first, f1.first * f2.second + f1.second}; }
    };
    struct Act
    {
        using T = MergeMonoid::T;
        using F = OpMonoid::F;
        T operator()(const F& f, const T& x) const { return {f.first * x.first + f.second * x.second, x.second}; }
    };

    const auto [N, Q] = in.tup<int, int>();
    std::vector<std::pair<mint, int>> as(N, {0, 1});
    for (int i = 0; i < N; i++) { as[i].first = in.val<mint>(); }
    auto seg = lazyseg<MergeMonoid, OpMonoid, Act>(as);
    for (int q = 0; q < Q; q++) {
        const auto t = in.val<int>();
        if (t == 0) {
            const auto [l, r, b, c] = in.tup<int, int, mint, mint>();
            seg.act(l, r, Func{b, c});
        } else {
            const auto [l, r] = in.tup<int, int>();
            out.ln(seg.fold(l, r).first());
        }
    }
    return 0;
}
