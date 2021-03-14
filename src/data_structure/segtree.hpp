#pragma once
#include <cassert>
#include <iostream>
#include <vector>
#include "../misc/bit_ops.hpp"
template<typename MergeMonoid>
class segtree
{
    using T = typename MergeMonoid::T;
    static constexpr T e() { return MergeMonoid::e(); }

public:
    segtree(const std::vector<T>& vs) : m_size{(int)vs.size()}, m_half{(int)ceil2(m_size)}, m_vals(m_half << 1, MergeMonoid::e()), m_merge{}
    {
        std::copy(vs.begin(), vs.end(), m_vals.begin() + m_half);
        for (int i = m_half - 1; i >= 1; i--) { up(i); }
    }
    T get(const int i) const { return assert(0 <= i and i < m_size), m_vals[i + m_half]; }
    void set(int i, const T& v)
    {
        assert(0 <= i and i < m_size);
        m_vals[i += m_half] = v;
        while (i >>= 1) { up(i); }
    }
    T fold(int l, int r) const
    {
        assert(0 <= l and l <= r and r <= m_size);
        T vl = e(), vr = e();
        for (l += m_half, r += m_half; l < r; l >>= 1, r >>= 1) {
            if (l & 1) { vl = m_merge(vl, m_vals[l++]); }
            if (r & 1) { vr = m_merge(m_vals[--r], vr); }
        }
        return m_merge(vl, vr);
    }
    friend std::ostream& operator<<(std::ostream& os, const segtree& seg)
    {
        os << "[";
        for (int i = seg.m_half; i < seg.m_half + seg.m_size; i++) { os << seg.m_vals[i] << (i + 1 == seg.m_half + seg.m_size ? "" : ","); }
        return (os << "]");
    }

private:
    void up(const int i) { m_vals[i] = m_merge(m_vals[i << 1], m_vals[i << 1 | 1]); }
    int m_size, m_half;
    std::vector<T> m_vals;
    const MergeMonoid m_merge;
};
