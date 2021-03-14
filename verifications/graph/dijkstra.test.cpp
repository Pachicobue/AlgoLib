#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"
#ifndef WITHOUT_STANDARD_LIBRARY
#    include <algorithm>
#endif
#include "graph/dijkstra.hpp"
#include "misc/fastio/printer.hpp"
#include "misc/fastio/scanner.hpp"
#include "misc/types.hpp"
int main()
{
    const auto [N, M, S, T] = in.tup<int, int, int, int>();
    graph<ll> g(N), rg(N);
    for (int i = 0; i < M; i++) {
        const auto [u, v, c] = in.tup<int, int, ll>();
        g.add_edge(u, v, c), rg.add_edge(v, u, c);
    }
    const auto ds = dijkstra(g, S);
    if (ds[T] >= inf_v<ll>) { return out.ln(-1); }
    using pii = std::pair<int, int>;
    std::vector<bool> used(N, false);
    std::vector<pii> ans;
    int p = T;
    while (p != S) {
        used[p] = true;
        for (const int ei : rg[p]) {
            [[maybe_unused]] const auto [from, pp, cost] = rg.edge(p, ei);
            if (not used[pp] and ds[pp] + cost == ds[p]) {
                ans.push_back({pp, p});
                p = pp;
                break;
            }
        }
    }
    std::reverse(ans.begin(), ans.end());
    out.ln(ds[T], ans.size());
    for (const auto& [u, v] : ans) { out.ln(u, v); }
    return 0;
}
