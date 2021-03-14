#pragma once
#include <cassert>
#include <iostream>
#include "../misc/types.hpp"
struct moddinfo64
{
    u64 mod{1}, r2{1}, inv{1};
    void set_mod(const u64 nmod)
    {
        assert(nmod < (1ULL << 62)), assert(nmod & 1);
        mod = nmod, r2 = -u128(mod) % mod;
        inv = mod;
        for (int i = 0; i < 5; i++) { inv *= 2 - mod * inv; }
        assert(inv * mod == 1);
    }
    u64 reduce(const u128& x) const { return (x + u128((u64)x * -inv) * mod) >> 64; }
};
template<const moddinfo64& info>
class moddint64
{
public:
    static constexpr const u64& mod = info.mod;
    constexpr moddint64() : m_val{0} {}
    constexpr moddint64(const i64 v) : m_val{info.reduce((u128(v) + mod) * info.r2)} {}
    constexpr moddint64 operator-() const { return moddint64{} - (*this); }
    constexpr moddint64& operator+=(const moddint64& m)
    {
        if (i64(m_val += m.m_val - 2 * mod) < 0) { m_val += 2 * mod; }
        return *this;
    }
    constexpr moddint64& operator-=(const moddint64& m)
    {
        if (i64(m_val -= m.m_val) < 0) { m_val += 2 * mod; }
        return *this;
    }
    constexpr moddint64& operator*=(const moddint64& m) { return m_val = info.reduce(u128(m_val) * m.m_val), *this; }
    constexpr moddint64& operator/=(const moddint64& m) { return *this *= m.inv(); }
    constexpr moddint64 operator+(const moddint64& m) const { return moddint64{*this} += m; }
    constexpr moddint64 operator-(const moddint64& m) const { return moddint64{*this} -= m; }
    constexpr moddint64 operator*(const moddint64& m) const { return moddint64{*this} *= m; }
    constexpr moddint64 operator/(const moddint64& m) const { return moddint64{*this} /= m; }
    constexpr bool operator==(const moddint64& m) const { return (m_val >= mod ? m_val - mod : m_val) == (m.m_val >= mod ? m.m_val - mod : m.m_val); }
    constexpr bool operator!=(const moddint64& m) const { return not(*this == m); }
    friend std::istream& operator>>(std::istream& is, moddint64& m)
    {
        i64 v;
        return is >> v, m = v, is;
    }
    friend std::ostream& operator<<(std::ostream& os, const moddint64& m) { return os << m(); }
    constexpr u64 get() const
    {
        const u64 m = info.reduce(m_val);
        return m >= mod ? m - mod : m;
    }
    constexpr u64 operator()() const { return get(); }
    constexpr moddint64 pow(u128 n) const
    {
        moddint64 ans = 1;
        for (moddint64 x = *this; n > 0; n >>= 1, x *= x) {
            if (n & 1) { ans *= x; }
        }
        return ans;
    }
    constexpr moddint64 inv() const { return pow(mod - 2); }

private:
    u64 m_val;
};
