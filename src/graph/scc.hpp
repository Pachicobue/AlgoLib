#pragma once
#include "graph.hpp"
template<typename T>
class sc_comp
{
public:
    sc_comp(const graph<T>& g) : m_size(g.size()), m_cmps(m_size, -1)
    {
        graph<T> rg(g.size());
        for (int i = 0; i < g.size(); i++) {
            for (const int ei : g[i]) {
                [[maybe_unused]] const auto [from, to, cost] = g.edge(i, ei);
                rg.add_edge(to, from, cost);
            }
        }
        std::vector<int> st;
        std::vector<bool> used(m_size, false);
        auto dfs1 = [&](auto self, const int s) -> void {
            used[s] = true;
            for (const int ei : g[s]) {
                [[maybe_unused]] const auto [from, to, cost] = g.edge(s, ei);
                if (not used[to]) { self(self, to); }
            }
            st.push_back(s);
        };
        auto dfs2 = [&](auto self, const int s) -> void {
            m_cmps[s] = m_cnum;
            for (const int ei : rg[s]) {
                [[maybe_unused]] const auto [from, to, cost] = rg.edge(s, ei);
                if (m_cmps[to] != -1) { continue; }
                self(self, to);
            }
        };
        for (int i = 0; i < m_size; i++) {
            if (used[i]) { continue; }
            dfs1(dfs1, i);
        }
        for (int i = (int)st.size() - 1; i >= 0; i--) {
            const int s = st[i];
            if (m_cmps[s] != -1) { continue; }
            dfs2(dfs2, s), m_cnum++;
        }
    }
    int operator[](const int v) const { return m_cmps[v]; }
    int cnum() const { return m_cnum; }

private:
    int m_size, m_cnum = 0;
    std::vector<int> m_cmps;
};
