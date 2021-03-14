#pragma once
#ifndef WITHOUT_STANDARD_LIBRARY
#    include <algorithm>
#endif
#include "graph.hpp"
template<typename T>
std::pair<int, std::vector<int>> diameter(const graph<T>& g)
{
    const int N = g.size();
    std::vector<T> ds(N, 0);
    std::vector<int> peis(N, -1);
    auto dfs = [&](auto self, const int u, const int p) -> void {
        for (const int ei : g[u]) {
            [[maybe_unused]] const auto& [from, to, cost] = g.edge(u, ei);
            if (to == p) { continue; }
            ds[to] = ds[u] + cost, peis[to] = ei;
            self(self, to, u);
        }
    };
    dfs(dfs, 0, -1);
    int r = std::max_element(ds.begin(), ds.end()) - ds.begin();
    ds[r] = 0, std::fill(peis.begin(), peis.end(), -1), dfs(dfs, r, -1);
    r     = std::max_element(ds.begin(), ds.end()) - ds.begin();
    std::vector<int> ans;
    for (int v = r; peis[v] != -1; v = std::get<1>(g.edge(v, peis[v]))) { ans.push_back(peis[v]); }
    return {r, ans};
}
