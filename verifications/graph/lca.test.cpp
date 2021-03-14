#define PROBLEM "https://judge.yosupo.jp/problem/lca"
#include "graph/lca.hpp"
#include "misc/fastio/printer.hpp"
#include "misc/fastio/scanner.hpp"
int main()
{
    const auto [N, Q] = in.tup<int, int>();
    graph g(N);
    for (int i = 1; i < N; i++) {
        const int p = in.val<int>();
        g.add_edge(p, i, true);
    }
    const auto lca = lca_manager(g, 0);
    for (int q = 0; q < Q; q++) {
        const auto [u, v] = in.tup<int, int>();
        const int l       = lca(u, v);
        out.ln(l);
    }
    return 0;
}
