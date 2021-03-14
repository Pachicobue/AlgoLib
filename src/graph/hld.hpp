#pragma once
#ifndef WITHOUT_STANDARD_LIBRARY
#    include <algorithm>
#    include <iostream>
#endif
#include "graph.hpp"
template<typename T>
class hl_decomp
{
public:
    hl_decomp(graph<T>& g, const int r = 0) : m_pars(g.size(), -1), m_tops{m_pars}, m_ins{m_pars}, m_ords{m_pars}, m_outs{m_pars}
    {
        const int N = g.size();
        std::vector<int> szs(N, 1);
        auto dfs1 = [&](auto self, const int u, const int p) -> int {
            m_pars[u] = p;
            for (int& ei : g[u]) {
                [[maybe_unused]] const auto& [from, to, cost] = g.edge(u, ei);
                if (p == to) { continue; }
                szs[u] += self(self, to, u);
                if (szs[std::get<1>(g.edge(u, g[u][0]))] < szs[to]) { std::swap(g[u][0], ei); }
            }
            return szs[u];
        };
        dfs1(dfs1, r, -1);
        m_tops[r] = r;
        auto dfs2 = [&](auto&& self, const int u, const int p, int& ind) -> void {
            m_ins[u] = ind++, m_ords[m_ins[u]] = u;
            for (const int ei : g[u]) {
                [[maybe_unused]] const auto& [from, to, cost] = g.edge(u, ei);
                if (to == p) { continue; }
                m_tops[to] = (ei == g[u][0] ? m_tops[u] : to);
                self(self, to, u, ind);
            }
            m_outs[u] = ind;
        };
        int ind = 0;
        dfs2(dfs2, r, -1, ind);
    }
    int pos(const int v) const { return m_ins[v]; }
    int at(const int n) const { return m_ords[n]; }
    std::pair<int, int> sub(const int v) const { return {m_ins[v], m_outs[v]}; }
    std::vector<std::pair<int, int>> path(int u, int v) const
    {
        using P = std::pair<int, int>;
        std::vector<P> head, tail;
        for (int pu = m_tops[u], pv = m_tops[v]; pu != pv;) {
            if (m_ins[pu] < m_ins[pv]) {
                tail.push_back({m_ins[pv], m_ins[v]});
                v = m_pars[pv], pv = m_tops[v];
            } else {
                head.push_back({m_ins[u], m_ins[pu]});
                u = m_pars[pu], pu = m_tops[u];
            }
        }
        head.push_back({m_ins[u], m_ins[v]});
        std::reverse(tail.begin(), tail.end());
        for (const auto& p : tail) { head.push_back(p); }
        return head;
    }
    friend std::ostream& operator<<(std::ostream& os, const hl_decomp& hld)
    {
        os << "ord = {";
        for (const int v : hld.m_ords) { os << v << ","; }
        os << "}\ntops = {";
        for (const int v : hld.m_tops) { os << v << ","; }
        return os << "}";
    }

private:
    std::vector<int> m_pars, m_tops, m_ins, m_ords, m_outs;
};
