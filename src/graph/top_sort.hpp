#pragma once
#ifndef WITHOUT_STANDARD_LIBRARY
#    include <algorithm>
#endif
#include "graph.hpp"
template<typename T>
std::pair<bool, std::vector<int>> top_sort(const graph<T>& g)
{
    const int v = g.size();
    std::vector<int> srt, used(v, 0);
    auto dfs = [&](auto self, const int s) -> bool {
        if (used[s] == 1) {
            return false;
        } else if (used[s] == 0) {
            used[s] = 1;
            for (const int ei : g[s]) {
                [[maybe_unused]] const auto [from, to, cost] = g.edge(s, ei);
                if (not self(self, to)) { return false; }
            }
            used[s] = 2, srt.push_back(s);
        }
        return true;
    };
    for (int i = 0; i < v; i++) {
        if (not dfs(dfs, i)) { return {false, srt}; }
    }
    std::reverse(srt.begin(), srt.end());
    return {true, srt};
}
