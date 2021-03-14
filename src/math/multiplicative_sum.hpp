#pragma once
#include "prime_powsum.hpp"
template<typename T, typename F>
class multiplicative_sum : public prime_powsum<T>
{
    using prime_powsum<T>::id;
    using prime_powsum<T>::m_ps;
    using prime_powsum<T>::m_ns;
    using prime_powsum<T>::m_hss;

public:
    static constexpr u32 MAXD = prime_powsum<T>::MAXD;
    multiplicative_sum(const u64 N, F f, const std::array<T, MAXD + 1>& coeffs) : prime_powsum<T>{N}, m_buf(m_ns.size(), 0), m_f{f}
    {
        for (u32 i = 0; i < m_buf.size(); i++) {
            for (u32 d = 0; d <= MAXD; d++) { m_buf[i] += coeffs[d] * m_hss[d][i]; }
        }
    }
    T get(const u64 n) const
    {
        T ans = m_buf[id(n)] + 1;
        for (u32 i = 0; i < m_ps.size(); i++) { ans += dfs(i, 1, m_ps[i], n / m_ps[i], 1); }
        return ans;
    }

private:
    T dfs(const u32 i, const u32 c, const u64 v, const u64 lim, T fv) const
    {
        T ans = fv * m_f(m_ps[i] * v, m_ps[i], c + 1);
        if (lim >= m_ps[i] * m_ps[i]) { ans += dfs(i, c + 1, m_ps[i] * v, lim / m_ps[i], fv); }
        fv *= m_f(v, m_ps[i], c);
        ans += fv * (m_buf[id(lim)] - m_buf[id(m_ps[i])]);
        for (u32 j = i + 1; j < m_ps.size() and m_ps[j] * m_ps[j] <= lim; j++) { ans += dfs(j, 1, m_ps[j], lim / m_ps[j], fv); }
        return ans;
    }
    std::vector<T> m_buf;
    F m_f;
};
