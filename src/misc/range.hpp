#pragma once
#ifndef WITHOUT_STANDARD_LIBRARY
#    include <cassert>
#    include <cmath>
#endif
class range
{
private:
    struct itr
    {
        itr(const int start = 0, const int step = 1) : m_cnt{start}, m_step{step} {}
        bool operator!=(const itr& it) const { return m_cnt != it.m_cnt; }
        int& operator*() { return m_cnt; }
        itr& operator++() { return m_cnt += m_step, *this; }
        int m_cnt, m_step;
    };
    int m_start, m_end, m_step;

public:
    range(const int start, const int end, const int step = 1) : m_start{start}, m_end{end}, m_step{step}
    {
        assert(m_step != 0);
        if (m_step > 0) { m_end = m_start + std::max(m_step - 1, m_end - m_start + m_step - 1) / m_step * m_step; }
        if (m_step < 0) { m_end = m_start - std::max(-m_step - 1, m_start - m_end - m_step - 1) / (-m_step) * (-m_step); }
    }
    itr begin() const { return itr{m_start, m_step}; }
    itr end() const { return itr{m_end, m_step}; }
};
range rep(const int end, const int step = 1) { return range(0, end, step); }
range per(const int rend, const int step = -1) { return range(rend - 1, -1, step); }
