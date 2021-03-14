#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include "data_structure/fenwick.hpp"
#include "misc/fastio/printer.hpp"
#include "misc/fastio/scanner.hpp"
int main()
{
    const auto [N, Q] = in.tup<int, int>();
    const auto as     = in.vec<u64>(N);
    auto bit          = fenwick(as);
    for (int q = 0; q < Q; q++) {
        const auto t = in.val<int>();
        if (t == 0) {
            const auto [p, x] = in.tup<int, u64>();
            bit.add(p, x);
        } else {
            const auto [l, r] = in.tup<int, int>();
            out.ln(bit.sum(l, r));
        }
    }
    return 0;
}
