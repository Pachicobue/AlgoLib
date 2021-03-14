#pragma once
#include "lowlink.hpp"
template<typename T>
class bc_comp
{
public:
    bc_comp(const graph<T>& g) : m_size{g.size()}, m_cs(m_size, -1), m_lowlink{g}
    {
        auto dfs = [&](auto self, const int u) -> void {
            m_cs[u] = m_cnum;
            for (const int ei : g[u]) {
                [[maybe_unused]] const auto& [from, to, cost] = g.edge(u, ei);
                if (m_cs[to] != -1 or m_lowlink.is_bridge(from, to)) { continue; }
                self(self, to);
            }
        };
        for (int i = 0; i < m_size; i++) {
            if (m_cs[i] != -1) { continue; }
            dfs(dfs, i), m_cnum++;
        }
    }
    int operator[](const int v) const { return m_cs[v]; }
    int cnum() const { return m_cnum; }

private:
    int m_size, m_cnum = 0;
    std::vector<int> m_cs;
    const lowlink_manager<T> m_lowlink;
};
