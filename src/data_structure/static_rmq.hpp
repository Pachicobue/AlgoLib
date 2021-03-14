#pragma once
#ifndef WITHOUT_STANDARD_LIBRARY
#    include <algorithm>
#    include <cassert>
#    include <functional>
#    include <stack>
#endif
#include "../misc/bit_ops.hpp"
#include "ds_table.hpp"
template<typename TotalOrd, typename B = ull>
class static_rmq
{
    using T = typename TotalOrd::T;

public:
    static_rmq(const std::vector<T>& vs)
        : m_comp{}, m_sz{(int)vs.size()}, m_bn{(int)wind(m_sz + bs - 1)}, m_vals{vs}, m_bucket_vals([&]() {
              std::vector<T> ans(m_bn);
              for (int i = 0; i < m_sz; i++) { ans[wind(i)] = i % bs == 0 ? m_vals[i] : std::min(ans[wind(i)], m_vals[i], m_comp); }
              return ans;
          }()),
          m_masks(m_sz, 0),
          m_st(m_bucket_vals)
    {
        for (int i = 0; i < m_bn; i++) {
            std::vector<int> g(bs, m_sz);
            std::stack<int> stack;
            for (int j = 0; j < bs and (int) ind(i, j) < m_sz; j++) {
                for (; not stack.empty() and not m_comp(m_vals[stack.top()], m_vals[ind(i, j)]); stack.pop()) {}
                g[j] = stack.empty() ? m_sz : stack.top(), stack.push(ind(i, j));
            }
            for (int j = 0; j < bs and (int) ind(i, j) < m_sz; j++) { m_masks[ind(i, j)] = g[j] == m_sz ? static_cast<B>(0) : (m_masks[g[j]] | static_cast<B>(1) << (g[j] - i * bs)); }
        }
    }
    T fold(const int l, const int r) const
    {
        assert(0 <= l and l < r and r <= m_sz);
        const int lb = (l + bs - 1) / bs, rb = r / bs;
        if (lb > rb) {
            return brmq(l, r);
        } else {
            return lb < rb
                       ? (l < bs * lb
                              ? (bs * rb < r
                                     ? std::min({m_st.fold(lb, rb), brmq(l, bs * lb), brmq(bs * rb, r)}, m_comp)
                                     : std::min(m_st.fold(lb, rb), brmq(l, bs * lb), m_comp))
                              : (bs * rb < r
                                     ? std::min(m_st.fold(lb, rb), brmq(bs * rb, r), m_comp)
                                     : m_st.fold(lb, rb)))
                       : (l < bs * lb
                              ? (bs * rb < r
                                     ? std::min(brmq(l, bs * lb), brmq(bs * rb, r), m_comp)
                                     : brmq(l, bs * lb))
                              : (bs * rb < r
                                     ? brmq(bs * rb, r)
                                     : T{}));
        }
    }

private:
    static constexpr int bs    = sizeof(B) * 8;
    static constexpr int bslog = log2p1(bs) - 1;
    static constexpr uint wind(const uint n) { return n >> (bslog); }
    static constexpr uint bind(const uint n) { return n ^ (wind(n) << bslog); }
    static constexpr uint ind(const uint w, const uint b) { return (w << bslog) | b; }
    T brmq(const int l, const int r) const
    {
        const B w = m_masks[r - 1] >> (l % bs);
        return w == 0 ? m_vals[r - 1] : m_vals[l + lsbp1(w) - 1];
    }
    struct SemiGroup
    {
        using T = typename TotalOrd::T;
        T operator()(const T& x1, const T& x2) const { return std::min(x1, x2, TotalOrd{}); }
    };
    const TotalOrd m_comp;
    int m_sz, m_bn;
    std::vector<T> m_vals, m_bucket_vals;
    std::vector<B> m_masks;
    ds_table<SemiGroup> m_st;
};
