#define PROBLEM "https://judge.yosupo.jp/problem/vertex_set_path_composite"
#include "data_structure/segtree.hpp"
#include "graph/hld.hpp"
#include "math/modint.hpp"
#include "misc/fastio/printer.hpp"
#include "misc/fastio/scanner.hpp"
int main()
{
    using mint        = modint_998244353;
    const auto [N, Q] = in.tup<int, int>();
    graph g(N);
    using Func = std::pair<mint, mint>;
    struct Monoid
    {
        using T = Func;
        static const T e() { return T{1, 0}; }
        T operator()(const T& f2, const T& f1) const { return T{f1.first * f2.first, f1.first * f2.second + f1.second}; }
    };
    struct RMonoid
    {
        using T = Func;
        static const T e() { return T{1, 0}; }
        T operator()(const T& f1, const T& f2) const { return T{f1.first * f2.first, f1.first * f2.second + f1.second}; }
    };

    std::vector<mint> as(N), bs(N);
    for (int i = 0; i < N; i++) { std::tie(as[i], bs[i]) = in.tup<mint, mint>(); }
    for (int i = 0; i < N - 1; i++) {
        const auto [u, v] = in.tup<int, int>();
        g.add_edge(u, v, true);
    }
    const hl_decomp hld{g};
    std::vector<Func> vs(N);
    for (int i = 0; i < N; i++) { vs[hld.pos(i)] = Func{as[i], bs[i]}; }
    auto seg  = segtree<Monoid>(vs);
    auto rseg = segtree<RMonoid>(vs);
    for (int q = 0; q < Q; q++) {
        const auto t = in.val<int>();
        if (t == 0) {
            const auto [p, c, d] = in.tup<int, mint, mint>();
            seg.set(hld.pos(p), {c, d}), rseg.set(hld.pos(p), {c, d});
        } else {
            const auto [u, v, x] = in.tup<int, int, mint>();
            const auto ps        = hld.path(u, v);
            Func f{1, 0};
            for (const auto& [a, b] : ps) { f = Monoid{}(f, a <= b ? seg.fold(a, b + 1) : rseg.fold(b, a + 1)); }
            out.ln((f.first * x + f.second)());
        }
    }
    return 0;
}
