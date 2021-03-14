#pragma once
#ifndef WITHOUT_STANDARD_LIBRARY
#    include <cassert>
#    include <iostream>
#    include <vector>
#endif
#include "../misc/bit_ops.hpp"
template<typename MergeMonoid, typename OpMonoid, typename Act>
class lazyseg
{
    using T = typename MergeMonoid::T;
    using F = typename OpMonoid::F;
    static constexpr T e() { return MergeMonoid::e(); }
    static constexpr F id() { return OpMonoid::id(); }

public:
    lazyseg(const std::vector<T>& vs) : m_size{(int)vs.size()},
                                        m_depth{clog(m_size)},
                                        m_half{1 << m_depth},
                                        m_vals(m_half << 1, MergeMonoid::e()),
                                        m_ops(m_half << 1, OpMonoid::id())
    {
        std::copy(vs.begin(), vs.end(), m_vals.begin() + m_half);
        for (int i = m_half - 1; i >= 1; i--) { up(i); }
    }
    T get(const int a) { return assert(a < m_size), fold(a, a + 1); }
    void set(int a, const T& v)
    {
        assert(0 <= a and a < m_size);
        top_down(a += m_half), top_down(a + 1), m_ops[a] = id(), m_vals[a] = v;
        while (a >>= 1) { up(a); }
    }
    T fold(int l, int r)
    {
        assert(0 <= l and l <= r and r <= m_size);
        if (l >= r) { return e(); }
        top_down(l += m_half), top_down(r += m_half);
        T accl = e(), accr = e();
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) { accl = m_merge(accl, m_vals[l++]); }
            if (r & 1) { accr = m_merge(m_vals[--r], accr); }
        }
        return m_merge(accl, accr);
    }
    void act(int l, int r, const F& f)
    {
        assert(0 <= l and l <= r and r <= m_size);
        const int lin = l + m_half, rin = r + m_half;
        top_down(l += m_half), top_down(r += m_half);
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) { update(l++, f); }
            if (r & 1) { update(--r, f); }
        }
        bottom_up(lin), bottom_up(rin);
    }
    friend std::ostream& operator<<(std::ostream& os, const lazyseg& lseg)
    {
        auto lseg2 = lseg;
        os << "[";
        for (int i = 0; i < lseg.m_size; i++) { os << lseg2.get(i) << (i + 1 == lseg2.m_size ? "" : ","); }
        return (os << "]\n");
    }

private:
    void up(const int i) { m_vals[i] = m_merge(m_vals[i << 1], m_vals[i << 1 | 1]); }
    void update(const int a, const F& f) { m_ops[a] = m_compose(f, m_ops[a]), m_vals[a] = m_apply(f, m_vals[a]); }
    void down(const int a) { update(a << 1, m_ops[a]), update(a << 1 | 1, m_ops[a]), m_ops[a] = id(); }
    void top_down(const int a)
    {
        const int b = (a / (a & -a)) >> 1;
        for (int i = 0; i < m_depth; i++) {
            const int v = a >> (m_depth - i);
            if (v > b) { break; }
            down(v);
        }
    }
    void bottom_up(int a)
    {
        a = (a / (a & -a)) >> 1;
        for (; a >= 1; a >>= 1) { up(a); }
    }
    int m_size, m_depth, m_half;
    std::vector<T> m_vals;
    std::vector<F> m_ops;
    static inline MergeMonoid m_merge;
    static inline OpMonoid m_compose;
    static inline Act m_apply;
};
