#define PROBLEM "https://judge.yosupo.jp/problem/line_add_get_min"
#include "data_structure/li_chao_tree.hpp"
#include "misc/constants.hpp"
#include "misc/fastio/printer.hpp"
#include "misc/fastio/scanner.hpp"
#include "misc/types.hpp"
int main()
{
    const auto [N, Q] = in.tup<int, int>();
    auto cht          = li_chao_tree<i64, i64>(-TEN<i64>(9), TEN<i64>(9));
    for (int i = 0; i < N; i++) {
        const auto [a, b] = in.tup<i64, i64>();
        cht.add_line(a, b);
    }
    for (int q = 0; q < Q; q++) {
        const auto t = in.val<int>();
        if (t == 0) {
            const auto [a, b] = in.tup<i64, i64>();
            cht.add_line(a, b);
        } else {
            const auto p = in.val<i64>();
            const auto l = cht.min_line(p);
            out.ln(l.first * p + l.second);
        }
    }
}
