#pragma once
#include "../data_structure/static_rmq.hpp"
#include "graph.hpp"
template<typename C>
class lca_manager
{
public:
    lca_manager(const graph<C>& g, const int r = 0) : m_ins(g.size(), 0),
                                                      m_ds([&]() {
                                                          std::vector<std::pair<int, int>> ans;
                                                          std::vector<bool> used(g.size(), false);
                                                          auto dfs = [&](auto self, const std::pair<int, int>& s) -> void {
                                                              const int pos = s.second;
                                                              used[pos] = true, m_ins[pos] = ans.size(), ans.push_back(s);
                                                              for (const int ei : g[pos]) {
                                                                  [[maybe_unused]] const auto& [from, to, cost] = g.edge(pos, ei);
                                                                  if (used[to]) { continue; }
                                                                  self(self, {s.first + 1, to}), ans.push_back(s);
                                                              }
                                                          };
                                                          dfs(dfs, {0, r});
                                                          return ans;
                                                      }()),
                                                      m_rmq(m_ds) {}
    int operator()(const int u, const int v) const
    {
        const int ul = m_ins[u], vl = m_ins[v];
        return m_rmq.fold(std::min(ul, vl), std::max(ul, vl) + 1).second;
    }

private:
    struct Ord
    {
        using T = std::pair<int, int>;
        bool operator()(const T& p1, const T& p2) const { return p1 < p2; }
    };
    std::vector<int> m_ins;
    std::vector<std::pair<int, int>> m_ds;
    static_rmq<Ord> m_rmq;
};
