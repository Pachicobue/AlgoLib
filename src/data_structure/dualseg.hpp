#pragma once
#include <cassert>
#include <iostream>
#include <vector>
#include "../misc/bit_ops.hpp"
template<typename OpMonoid>
class dualseg
{
    using F = typename OpMonoid::F;
    static constexpr F id() { return OpMonoid::id(); }

public:
    dualseg(const std::vector<F>& vs) : m_size{(int)vs.size()}, m_depth{(int)clog(m_size)}, m_half{1 << m_depth}, m_ops(m_half << 1, OpMonoid::id()) { std::copy(vs.begin(), vs.end(), m_ops.begin() + m_half); }
    F get(const int a) const
    {
        assert(0 <= a and a < m_size);
        F ans = id();
        for (int i = 0; i <= m_depth; i++) { ans = m_compose(ans, m_ops[(a + m_half) >> (m_depth - i)]); }
        return ans;
    }
    void set(int a, const F& f)
    {
        assert(0 <= a and a < m_size);
        clean(a += m_half), clean(a + 1), m_ops[a] = f;
    }
    void act(int L, int R, const F& f)
    {
        assert(0 <= L and R <= m_size);
        if (L >= R) { return; }
        clean(L += m_half), clean(R += m_half);
        for (; L < R; L >>= 1, R >>= 1) {
            if (L & 1) { update(L++, f); }
            if (R & 1) { update(--R, f); }
        }
    }
    friend std::ostream& operator<<(std::ostream& os, const dualseg& seg)
    {
        os << "[";
        for (int i = 0; i < seg.m_size; i++) { os << seg.get(i) << (i + 1 == seg.m_size ? "" : ","); }
        return (os << "]\n");
    }

private:
    void down(const int a) { update(a << 1, m_ops[a]), update(a << 1 | 1, m_ops[a]), m_ops[a] = id(); }
    void clean(const int a)
    {
        const int b = (a / (a & -a)) >> 1;
        for (int i = 0; i < m_depth; i++) {
            const int v = a >> (m_depth - i);
            if (v > b) { break; }
            down(v);
        }
    }
    void update(const int a, const F& f) { m_ops[a] = m_compose(f, m_ops[a]); }
    int m_size, m_depth, m_half;
    std::vector<F> m_ops;
    static inline OpMonoid m_compose;
};
