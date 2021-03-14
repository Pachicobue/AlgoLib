#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"
#include "data_structure/unionfind.hpp"
#include "misc/fastio/printer.hpp"
#include "misc/fastio/scanner.hpp"
int main()
{
    const auto [N, Q] = in.tup<int, int>();
    auto uf           = unionfind(N);
    for (int q = 0; q < Q; q++) {
        const auto [t, u, v] = in.tup<int, int, int>();
        if (t == 0) {
            uf.unite(u, v);
        } else {
            out.ln(uf.root_of(u) == uf.root_of(v));
        }
    }
}
