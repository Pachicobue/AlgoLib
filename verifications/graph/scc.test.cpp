#define PROBLEM "https://judge.yosupo.jp/problem/scc"
#include "graph/scc.hpp"
#include "graph/top_sort.hpp"
#include "misc/fastio/printer.hpp"
#include "misc/fastio/scanner.hpp"
int main()
{
    const auto [N, M] = in.tup<int, int>();
    graph g(N);
    for (int i = 0; i < M; i++) {
        const auto [a, b] = in.tup<int, int>();
        g.add_edge(a, b);
    }
    const auto scc = sc_comp(g);
    const int C    = scc.cnum();
    graph dag(C);
    for (int u = 0; u < N; u++) {
        const int uc = scc[u];
        for (const int ei : g[u]) {
            [[maybe_unused]] const auto [from, v, cost] = g.edge(u, ei);
            const int vc                                = scc[v];
            if (uc == vc) { continue; }
            dag.add_edge(uc, vc);
        }
    }
    std::vector<std::vector<int>> cvs(C);
    for (int i = 0; i < N; i++) { cvs[scc[i]].push_back(i); }
    const auto [flag, cs] = top_sort(dag);
    out.ln(C);
    for (const int c : cs) { out.ln(cvs[c].size(), cvs[c]); }
    return 0;
}
