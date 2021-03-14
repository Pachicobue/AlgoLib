#pragma once
#include "../misc/constants.hpp"
#include "graph.hpp"
template<typename T>
std::vector<T> bellman_ford(const graph<T>& g, const int s)
{
    const int N = g.size();
    std::vector<T> ds(N, inf_v<T>);
    ds[s] = 0;
    for (int loop = 1; loop <= N + N; loop++) {
        for (int u = 0; u < N; u++) {
            if (ds[u] == inf_v<T>) { continue; }
            for (const int ei : g[u]) {
                [[maybe_unused]] const auto& [from, to, cost] = g.edge(u, ei);
                if (ds[to] <= ds[from] + cost) { continue; }
                ds[to] = ds[from] + cost;
                if (loop >= N) { ds[to] = -inf_v<T>; }
            }
        }
    }
    return ds;
}
