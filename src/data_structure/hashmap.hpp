#pragma once
#include <array>
#include <bitset>
#include "../misc/types.hpp"

template<typename K, typename V, int LG = 20>
class hashmap
{
public:
    hashmap() = default;
    V& operator[](const K& k)
    {
        for (uint i = hash(k);; (i += 1) &= (N - 1)) {
            if (not m_used.test(i)) {
                m_keys[i]        = k, m_used.set(i);
                return m_vals[i] = V{};
            }
            if (m_keys[i] == k) { return m_vals[i]; }
        }
    }
    void erase(const K& k) const
    {
        uint i = 0;
        for (i = hash(k); m_used.test(i) and m_keys[i] != k; (i += 1) &= (N - 1)) {}
        if (m_used.test(i) and m_keys[i] == k) { m_used.reset(i); }
    }
    int count(const K& k) const
    {
        uint i = 0;
        for (i = hash(k); m_used.test(i) and m_keys[i] != k; (i += 1) &= (N - 1)) {}
        return m_used.test(i) and m_keys[i] == k;
    }

private:
    static constexpr int N = 1 << LG;
    static constexpr ull r = 11995408973635179863ULL;
    static constexpr uint hash(const ull a) { return (a * r) >> (64 - LG); }
    std::bitset<N> m_used;
    std::array<K, N> m_keys;
    std::array<V, N> m_vals;
};
