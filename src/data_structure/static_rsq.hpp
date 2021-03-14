#pragma once
#ifndef WITHOUT_STANDARD_LIBRARY
#    include <cassert>
#    include <iostream>
#    include <vector>
#endif
template<typename T>
class static_rsq
{
public:
    static_rsq() = default;
    void push_back(const T& v) { m_sums.push_back(m_sums.back() + v); }
    T operator()(const int l, const int r) const { return m_sums[r] - m_sums[l]; }

private:
    std::vector<T> m_sums{T{}};
};
