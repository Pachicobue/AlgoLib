#pragma once
#include "graph.hpp"
template<typename T>
class centroid
{
public:
    centroid(const graph<T>& g) : m_g{g}, m_cs(m_g.size()), m_sub_calced{false}, m_subss(m_g.size()), m_subsss(m_g.size())
    {
        const int N = m_g.size();
        std::vector<int> szs(N, 1);
        std::vector<bool> used(N, false);
        auto size = [&](auto self, const int s, const int p) -> int {
            szs[s] = 1;
            for (const int ei : m_g[s]) {
                [[maybe_unused]] const auto& [from, to, cost] = m_g.edge(s, ei);
                if (to == p or used[to]) { continue; }
                szs[s] += self(self, to, s);
            }
            return szs[s];
        };
        auto search = [&](auto self, const int s, const int p, const int tot) -> int {
            for (const int ei : m_g[s]) {
                [[maybe_unused]] const auto& [from, to, cost] = m_g.edge(s, ei);
                if (p == to or used[to]) { continue; }
                if (szs[to] * 2 > tot) { return self(self, to, s, tot); }
            }
            if (tot == N) { m_center = s; }
            return s;
        };
        auto build = [&](auto self, const int s, const int pc) -> int {
            const int tot = size(size, s, N), c = search(search, s, N, tot);
            used[c] = true;
            if (pc != N) { m_cs.add_edge(pc, c); }
            for (const int ei : m_g[s]) {
                [[maybe_unused]] const auto& [from, to, cost] = m_g.edge(s, ei);
                if (not used[to]) { self(self, to, c); }
            }
            return c;
        };
        build(build, 0, N);
    }
    const graph<>& centros() const { return m_cs; }
    const std::vector<int>& subs(const int v) { return calc_sub(), m_subss[v]; }
    const std::vector<std::vector<int>>& subss(const int v) { return calc_sub(), m_subsss[v]; }

private:
    void calc_sub()
    {
        if (not m_sub_calced) {
            const int N = m_g.size();
            std::vector<bool> used(N, false);
            auto dfs = [&](auto self, const int c) -> void {
                used[c] = true;
                m_subss[c].push_back(c);
                for (const int ei : m_g[c]) {
                    [[maybe_unused]] const auto& [from, to, cost] = m_g.edge(c, ei);
                    if (used[to]) { continue; }
                    m_subsss[c].push_back(std::vector<int>{});
                    auto dfs2 = [&](auto selfself, const int s, const int p) -> void {
                        for (const int eiei : m_g[s]) {
                            [[maybe_unused]] const auto& [fromfrom, toto, costcost] = m_g.edge(s, eiei);
                            if (p == toto or used[toto]) { continue; }
                            m_subss[c].push_back(toto);
                            m_subsss[c].back().push_back(toto);
                            selfself(selfself, toto, s);
                        }
                    };
                    dfs2(dfs2, to, -1);
                }
                for (const int ei : m_g[c]) {
                    [[maybe_unused]] const auto& [from, to, cost] = m_cs.edge(c, ei);
                    self(self, to);
                }
            };
            dfs(dfs, m_center);
        }
        m_sub_calced = true;
    }
    graph<T> m_g;
    int m_center;
    graph<> m_cs;
    bool m_sub_calced;
    std::vector<std::vector<int>> m_subss;
    std::vector<std::vector<std::vector<int>>> m_subsss;
};
