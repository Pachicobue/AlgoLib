#pragma once
#ifndef WITHOUT_STANDARD_LIBRARY
#    include <limits>
#endif
#include "../misc/constants.hpp"
#include "graph.hpp"
template<typename T>
std::vector<std::vector<T>> warshall_floyd(const base_graph<T>& g)
{
    const int N = g.size();
    std::vector<std::vector<T>> d(N, std::vector<T>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) { d[i][j] = i == j ? T{} : inf_v<T>; }
        for (const int ei : g[i]) {
            [[maybe_unused]] const auto& [from, to, cost] = g.edge(i, ei);
            d[i][to]                                      = std::min(cost, d[i][to]);
        }
    }
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (d[i][k] == inf_v<T> or d[k][j] == inf_v<T>) { continue; }
                d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
    return d;
}
