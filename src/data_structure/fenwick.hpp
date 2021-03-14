#pragma once
#include <cassert>
#include <iostream>
#include <vector>
#include "../misc/bit_ops.hpp"
template<typename T>
class fenwick
{
public:
    fenwick(const std::vector<T>& vs) : m_size{(int)vs.size()}, m_cap{(int)ceil2(m_size)}, m_vals(m_cap + 1, 0)
    {
        std::copy(vs.begin(), vs.end(), m_vals.begin() + 1);
        for (int x = 1; x < m_cap; x++) { m_vals[x + (x & -x)] += m_vals[x]; }
    }
    void add(const int a, const T& v)
    {
        assert(0 <= a and a < m_size);
        for (int ind = a + 1; ind <= m_cap; ind += ind & (-ind)) { m_vals[ind] += v; }
    }
    T sum(const int a) const
    {
        assert(0 <= a and a <= m_size);
        T sum{};
        for (int ind = a; ind != 0; ind &= ind - 1) { sum += m_vals[ind]; }
        return sum;
    }
    T sum(const int l, const int r) const { return assert(0 <= l and l <= r and r <= m_size), sum(r) - sum(l); }
    template<typename F>
    int max_right(F f)
    {
        assert(f(T{}));
        T sum = T{};
        int x = 0;
        for (int k = (m_cap >> 1); k >= 1; k >>= 1) {
            if (x + k <= m_size and f(sum + m_vals[x + k])) { sum += m_vals[x + k], x += k; }
        }
        return x;
    }
    friend std::ostream& operator<<(std::ostream& os, const fenwick& fw)
    {
        os << "[";
        for (int i = 0; i < fw.m_size; i++) { os << fw.sum(i, i + 1) << (i + 1 == fw.sz ? "" : ","); }
        return (os << "]\n");
    }

private:
    int m_size, m_cap;
    std::vector<T> m_vals;
};
