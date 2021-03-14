#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#include "data_structure/static_rmq.hpp"
#include "misc/fastio/printer.hpp"
#include "misc/fastio/scanner.hpp"
int main()
{
    const auto [N, Q] = in.tup<int, int>();
    const auto as     = in.vec<u64>(N);
    struct SemiGroup
    {
        using T = u64;
        T operator()(const T x1, const T& x2) const { return std::min(x1, x2); }
    };
    const auto rmq = ds_table<SemiGroup>(as);
    for (int q = 0; q < Q; q++) {
        const auto [l, r] = in.tup<int, int>();
        out.ln(rmq.fold(l, r));
    }
}
