#pragma once
#ifndef WITHOUT_STANDARD_LIBRARY
#    include <algorithm>
#endif
#include "graph.hpp"
template<typename T>
class lowlink_manager
{
private:
    using P = std::pair<int, int>;
    int sz;
    std::vector<P> bs;
    std::vector<int> ords, lows, as;
    std::vector<bool> is_a;
    std::vector<std::vector<int>> dfs_tree;

public:
    lowlink_manager(const graph<T>& g) : sz(g.size()), ords(sz, sz), lows(sz, sz), is_a(sz, false), dfs_tree(sz)
    {
        int num  = 0;
        auto dfs = [&](auto self, const int s, const int p) -> void {
            ords[s] = lows[s] = num++;
            int back          = 0;
            for (const int ei : g[s]) {
                [[maybe_unused]] const auto [from, to, cost] = g.edge(s, ei);
                if (ords[to] == sz) {
                    dfs_tree[s].push_back(to), self(self, to, s), lows[s] = std::min(lows[s], lows[to]);
                } else {
                    if (p == to) { back++; }
                    if (p != to or back > 1) { lows[s] = std::min(lows[s], ords[to]); }
                }
            }
        };
        auto dfs2 = [&](auto&& self, const int s) -> void {
            int max = 0;
            for (const int to : dfs_tree[s]) {
                max = std::max(max, lows[to]);
                if (this->is_bridge(s, to)) { bs.push_back(std::minmax(s, to)); }
                self(self, to);
            }
            is_a[s] = ords[s] <= max and (s != 0 or dfs_tree[s].size() > 1);
            if (is_a[s]) { as.push_back(s); }
        };
        for (int i = 0; i < sz; i++) {
            if (ords[i] != sz) { continue; }
            dfs(dfs, i, sz), dfs2(dfs2, i);
        }
    }
    bool is_art(const int i) const { return is_a[i]; }
    bool is_bridge(const int i, const int j) const { return (ords[i] < ords[j]) ? ords[i] < lows[j] : ords[j] < lows[i]; }
    const std::vector<P>& bridges() const { return bs; }
    const std::vector<int>& arts() const { return as; }
};
