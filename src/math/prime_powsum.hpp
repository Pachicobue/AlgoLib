#pragma once
#include <array>
#include <cassert>
#include <cmath>
#include <vector>
#include "../misc/types.hpp"
template<typename T>
class prime_powsum
{
public:
    static constexpr u32 MAXD = 2;
    prime_powsum(const u64 N) : m_N{N}, m_sqrt{(u32)std::sqrt(N)}, m_ns{0}
    {
        assert(N >= 2);
        for (u64 i = N; i > 0; i = N / (N / i + 1)) { m_ns.push_back(i); }
        for (const auto n : m_ns) {
            const T x = n;
            m_hss[0].push_back(x - 1);
            m_hss[1].push_back(x * (x + 1) / 2 - 1);
            m_hss[2].push_back(x * (x + 1) * (x * 2 + 1) / 6 - 1);
        }
        for (u32 x = 2; x <= m_sqrt; x++) {
            if (m_hss[0][m_ns.size() - x] == m_hss[0][m_ns.size() - x + 1]) { continue; }
            m_ps.push_back(x);
            const u64 y = (u64)x * x;
            for (u32 i = 1; i < m_ns.size(); i++) {
                const u64 n = m_ns[i];
                if (n < y) { break; }
                const u32 j = (i * x <= m_sqrt ? i * x : m_ns.size() - n / x);
                const u32 k = m_ns.size() - x + 1;
                m_hss[0][i] -= (m_hss[0][j] - m_hss[0][k]);
                m_hss[1][i] -= (m_hss[1][j] - m_hss[1][k]) * x;
                m_hss[2][i] -= (m_hss[2][j] - m_hss[2][k]) * x * x;
            }
        }
    }
    T get(const u32 d, const u64 n) const
    {
        const u32 i = id(n);
        assert(m_ns[i] == n);
        return m_hss[d][i];
    }

protected:
    u32 id(const u64 x) const { return x <= m_sqrt ? m_ns.size() - x : m_N / x; }

    u64 m_N;
    u32 m_sqrt;
    std::vector<u64> m_ns, m_ps;
    std::array<std::vector<T>, MAXD + 1> m_hss;
};
