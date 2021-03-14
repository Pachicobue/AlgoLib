#pragma once
#include <cassert>
#include <deque>
#include <limits>
template<typename T, typename V = T>
class monotonic_cht
{
    using L = std::pair<T, T>;
    static bool needless(const L& l1, const L& l2, const L& l3)
    {
        const auto [a1, b1] = l1;
        const auto [a2, b2] = l2;
        const auto [a3, b3] = l3;
        return V(a1 - a3) * V(b2 - b1) >= V(a1 - a2) * V(b3 - b1) or V(a2 - a3) * V(b3 - b1) >= V(a1 - a3) * V(b3 - b2);
    }
    static bool comp(const L& l1, const L& l2, const T x) { return V(l1.first) * V(x) + V(l1.second) < V(l2.first) * V(x) + V(l2.second); }

public:
    monotonic_cht(const bool query_inc = true) : m_query_inc{query_inc}, m_prev_x{m_query_inc ? std::numeric_limits<T>::min() : std::numeric_limits<T>::max()} {}
    void add_line(const T a, const T b)
    {
        const L l{a, b};
        if (m_lines.empty()) { return m_lines.push_back(l), void(0); }
        const auto Ma = m_lines.front().first, ma = m_lines.back().first;
        assert(a < ma or Ma < a);
        if (Ma < a) {
            while (m_lines.size() >= 2 and needless(l, m_lines[0], m_lines[1])) { m_lines.pop_front(); }
            m_lines.push_front(l);
        } else {
            while (m_lines.size() >= 2 and needless(m_lines[m_lines.size() - 2], m_lines[m_lines.size() - 1], l)) { m_lines.pop_back(); }
            m_lines.push_back(l);
        }
    }
    L min_line(const T x)
    {
        if (m_lines.empty()) { return L{0, std::numeric_limits<T>::max()}; }
        if (m_query_inc) {
            assert(m_prev_x <= x);
            while (m_lines.size() >= 2 and not comp(m_lines[0], m_lines[1], x)) { m_lines.pop_front(); }
            return m_prev_x = x, m_lines.front();
        } else {
            assert(x <= m_prev_x);
            while (m_lines.size() >= 2 and not comp(m_lines[m_lines.size() - 1], m_lines[m_lines.size() - 2], x)) { m_lines.pop_back(); }
            return m_prev_x = x, m_lines.back();
        }
    }

private:
    bool m_query_inc;
    T m_prev_x;
    std::deque<L> m_lines;
};
