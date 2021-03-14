#pragma once
#include <cassert>
#include <iostream>
#include "../misc/types.hpp"
struct moddinfo
{
    u32 mod{1}, r2{1}, inv{1};
    void set_mod(const u32 nmod)
    {
        assert(nmod < (1ULL << 30)), assert(nmod & 1);
        mod = nmod, r2 = -u64(mod) % mod;
        inv = mod;
        for (int i = 0; i < 4; i++) { inv *= 2 - mod * inv; }
        assert(inv * mod == 1);
    }
    u32 reduce(const u64 x) const { return (x + u64(u32(x) * u32(-inv)) * mod) >> 32; }
};
template<const moddinfo& info>
class moddint
{
public:
    static constexpr const u32& mod = info.mod;
    constexpr moddint() : m_val{0} {}
    constexpr moddint(const i64 v) : m_val{info.reduce(u64(v % mod + mod) * info.r2)} {}
    constexpr moddint operator-() const { return moddint{} - (*this); }
    constexpr moddint& operator+=(const moddint& m)
    {
        if (i32(m_val += m.m_val - 2 * mod) < 0) { m_val += 2 * mod; }
        return *this;
    }
    constexpr moddint& operator-=(const moddint& m)
    {
        if (i32(m_val -= m.m_val) < 0) { m_val += 2 * mod; }
        return *this;
    }
    constexpr moddint& operator*=(const moddint& m) { return m_val = info.reduce(u64(m_val) * m.m_val), *this; }
    constexpr moddint& operator/=(const moddint& m) { return *this *= m.inv(); }
    constexpr moddint operator+(const moddint& m) const { return moddint{*this} += m; }
    constexpr moddint operator-(const moddint& m) const { return moddint{*this} -= m; }
    constexpr moddint operator*(const moddint& m) const { return moddint{*this} *= m; }
    constexpr moddint operator/(const moddint& m) const { return moddint{*this} /= m; }
    constexpr bool operator==(const moddint& m) const { return (m_val >= mod ? m_val - mod : m_val) == (m.m_val >= mod ? m.m_val - mod : m.m_val); }
    constexpr bool operator!=(const moddint& m) const { return not(*this == m); }
    friend std::istream& operator>>(std::istream& is, moddint& m)
    {
        i64 v;
        return is >> v, m = v, is;
    }
    friend std::ostream& operator<<(std::ostream& os, const moddint& m) { return os << m(); }
    constexpr u32 get() const
    {
        const u32 m = info.reduce(m_val);
        return m >= mod ? m - mod : m;
    }
    constexpr u32 operator()() const { return get(); }
    constexpr moddint pow(u64 n) const
    {
        moddint ans = 1;
        for (moddint x = *this; n > 0; n >>= 1, x *= x) {
            if (n & 1) { ans *= x; }
        }
        return ans;
    }
    constexpr moddint inv() const { return pow(mod - 2); }

private:
    u32 m_val;
};
