#pragma once
#ifndef WITHOUT_STANDARD_LIBRARY
#    include <iostream>
#    include <tuple>
#    include <vector>
#endif
template<typename T = int>
class graph
{
public:
    graph(const int sz) : m_size{sz}, m_eis(sz) {}
    void add_edge(const int u, const int v, const T c, const bool bi = false)
    {
        const int ei = (int)m_us.size();
        m_us.push_back(u), m_vs.push_back(v), m_cs.push_back(c);
        m_eis[u].push_back(ei);
        if (bi) { m_eis[v].push_back(ei); }
    }
    void add_edge(const int u, const int v, const bool bi = false) { add_edge(u, v, T{1}, bi); }
    std::tuple<int, int, T> edge(const int u, const int i) const { return std::make_tuple(u, m_us[i] ^ m_vs[i] ^ u, m_cs[i]); }
    const std::vector<int>& operator[](const int u) const { return m_eis[u]; }
    std::vector<int>& operator[](const int u) { return m_eis[u]; }
    int size() const { return m_size; }
    friend std::ostream& operator<<(std::ostream& os, const graph& g)
    {
        for (int u = 0; u < g.size(); u++) {
            for (const int ei : g[u]) {
                const auto [from, to, cost] = g.edge(u, ei);
                os << "[" << ei << "]: " << from << "->" << to << "(" << cost << ")\n";
            }
        }
        return os;
    }

private:
    int m_size;
    std::vector<int> m_us, m_vs;
    std::vector<T> m_cs;
    std::vector<std::vector<int>> m_eis;
};
