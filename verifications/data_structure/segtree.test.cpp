#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"
#include "data_structure/segtree.hpp"
#include "math/modint.hpp"
#include "misc/fastio/printer.hpp"
#include "misc/fastio/scanner.hpp"
int main()
{
    using mint = modint_998244353;
    using Func = std::pair<mint, mint>;
    struct Monoid
    {
        using T = Func;
        static const T e() { return T{1, 0}; }
        T operator()(const T& f2, const T& f1) const { return T{f1.first * f2.first, f1.first * f2.second + f1.second}; }
    };

    const auto [N, Q] = in.tup<int, int>();
    std::vector<Func> fs(N);
    for (int i = 0; i < N; i++) { std::tie(fs[i].first, fs[i].second) = in.tup<mint, mint>(); }
    auto seg = segtree<Monoid>(fs);
    for (int q = 0; q < Q; q++) {
        const auto t = in.val<int>();
        if (t == 0) {
            const auto [p, c, d] = in.tup<int, mint, mint>();
            seg.set(p, Func{c, d});
        } else {
            const auto [l, r, x] = in.tup<int, int, mint>();
            const auto [a, b]    = seg.fold(l, r);
            out.ln((a * x + b)());
        }
    }
    return 0;
}
