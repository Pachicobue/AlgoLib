#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"
#include "graph/bcc.hpp"
#include "misc/fastio/printer.hpp"
#include "misc/fastio/scanner.hpp"
int main()
{
    const auto [N, M] = in.tup<int, int>();
    graph g(N);
    for (int i = 0; i < M; i++) {
        const auto [a, b] = in.tup<int, int>();
        g.add_edge(a, b, true);
    }
    const auto bcc = bc_comp(g);
    const int C    = bcc.cnum();
    std::vector<std::vector<int>> cvs(C);
    for (int i = 0; i < N; i++) { cvs[bcc[i]].push_back(i); }
    out.ln(C);
    for (int c = 0; c < C; c++) { out.ln(cvs[c].size(), cvs[c]); }
    return 0;
}
