#pragma once
#ifndef WITHOUT_STANDARD_LIBRARY
#    include <queue>
#endif
#include "../misc/constants.hpp"
#include "graph.hpp"
template<typename T>
std::vector<T> dijkstra(const graph<T>& g, const int s)
{
    std::vector<T> ds(g.size(), inf_v<T>);
    using P = std::pair<T, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> Q;
    ds[s] = 0, Q.push({0, s});
    while (not Q.empty()) {
        const auto [c, u] = Q.top();
        Q.pop();
        if (ds[u] < c) { continue; }
        for (const int ei : g[u]) {
            [[maybe_unused]] const auto& [from, to, cost] = g.edge(u, ei);
            if (ds[to] <= ds[from] + cost) { continue; }
            ds[to] = ds[from] + cost, Q.push({ds[to], to});
        }
    }
    return ds;
}
