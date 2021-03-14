#pragma once
#ifndef WITHOUT_STANDARD_LIBRARY
#    include <cassert>
#    include <iostream>
#    include <numeric>
#    include <vector>
#endif
class unionfind
{
public:
    unionfind(const int sz) : m_sz{sz}, m_rt_or_size(m_sz, -1) { ; }
    int root_of(const int a) { return m_rt_or_size[a] < 0 ? a : m_rt_or_size[a] = root_of(m_rt_or_size[a]); }
    bool unite(int a, int b)
    {
        assert(a < m_sz), assert(b < m_sz), a = root_of(a), b = root_of(b);
        if (a == b) { return false; }
        if (-m_rt_or_size[a] < -m_rt_or_size[b]) { std::swap(a, b); }
        return m_rt_or_size[a] += m_rt_or_size[b], m_rt_or_size[b] = a, true;
    }
    int size_of(const int a) { return assert(a < m_sz), -m_rt_or_size[root_of(a)]; }

private:
    int m_sz;
    std::vector<int> m_rt_or_size;
};
