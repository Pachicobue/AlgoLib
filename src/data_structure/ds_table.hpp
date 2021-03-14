#pragma once
#include <cassert>
#include <vector>
#include "../misc/bit_ops.hpp"
template<typename SemiGroup>
class ds_table
{
    using T = typename SemiGroup::T;

public:
    ds_table(const std::vector<T>& vs) : m_size{(int)vs.size()}, m_depth{(int)log2p1(m_size)}, m_vss(m_depth, vs)
    {
        for (int d = 0; d < m_depth; d++) {
            const int width = 1 << (m_depth - d - 1);
            for (int i = 1; i * width < m_size; i += 2) {
                int l = i * width - 1, r = i * width;
                for (int j = 1; j < width; j++) {
                    m_vss[d][l - j] = m_merge(vs[l - j], m_vss[d][l - j + 1]);
                    if (r + j < m_size) { m_vss[d][r + j] = m_merge(vs[r + j], m_vss[d][r + j - 1]); }
                }
            }
        }
    }
    T fold(const int l, const int r) const
    {
        assert(0 <= l and l < r and r <= m_size);
        if (r - l == 1) { return m_vss.back()[l]; }
        const int d = m_depth - log2p1(l ^ (r - 1));
        return m_merge(m_vss[d][l], m_vss[d][r - 1]);
    }

private:
    int m_size, m_depth;
    std::vector<std::vector<T>> m_vss;
    static inline SemiGroup m_merge;
};
