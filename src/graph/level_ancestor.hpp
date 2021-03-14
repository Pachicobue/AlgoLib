#pragma once
#include "../misc/bit_ops.hpp"
#include "graph.hpp"
class level_ancestor
{
public:
    level_ancestor(const graph<int>& g, const int r = 0) : m_ds(g.size(), 0), m_ps(g.size())
    {
        auto dfs = [&](auto self, const int u, const int p) -> void {
            for (int k = 1; (1 << k) <= m_ds[u]; k++) { m_ps[u].push_back(m_ps[m_ps[u][k - 1]][k - 1]); }
            for (const int ei : g[u]) {
                [[maybe_unused]] const auto& [from, to, cost] = g.edge(u, ei);
                if (to == p) { continue; }
                m_ds[to] = m_ds[u] + cost, m_ps[to].push_back(u);
                self(self, to, u);
            }
        };
        dfs(dfs, r, -1);
    };
    int lca(int u, int v) const
    {
        if (m_ds[u] > m_ds[v]) { std::swap(u, v); }
        v = (*this)(v, m_ds[v] - m_ds[u]);
        if (u == v) { return u; }
        while (true) {
            if (m_ps[u][0] == m_ps[v][0]) { return m_ps[u][0]; }
            for (int i = m_ps[u].size() - 1; i >= 0; i--) {
                const int nu = m_ps[u][i], nv = m_ps[v][i];
                if (nu != nv) {
                    u = nu, v = nv;
                    break;
                }
            }
        }
    }
    int operator()(int v, const int d) const
    {
        for (int k = (int)log2p1(d); k >= 0; k--) {
            if (btest(d, k)) { v = m_ps[v][(int)k]; }
        }
        return v;
    }

private:
    std::vector<int> m_ds;
    std::vector<std::vector<int>> m_ps;
};
