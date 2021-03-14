#pragma once
#include <iostream>
#include <vector>
#include "../misc/types.hpp"
struct modinfo64
{
    void set_mod(const u64 nmod) { mod = nmod; }
    u64 mod;
};
template<const modinfo64& info>
class modint64
{
public:
    static constexpr const u64& mod = info.mod;
    constexpr modint64() : m_val{0} {}
    constexpr modint64(const ll v) : m_val{normll(v)} {}
    constexpr void set_raw(const u64 v) { m_val = v; }
    constexpr modint64 operator+() const { return *this; }
    constexpr modint64 operator-() const { return modint64{0} - (*this); }
    constexpr modint64& operator+=(const modint64& m) { return m_val = norm(m_val + m()), *this; }
    constexpr modint64& operator-=(const modint64& m) { return m_val = norm(m_val + mod - m()), *this; }
    constexpr modint64& operator*=(const modint64& m)
    {
        const i64 ans = m_val * m.m_val - (i64)((f80)m_val * m.m_val / mod + 0.5) * mod;
        return m_val  = (u64)(ans < 0 ? ans + mod : ans), *this;
    }
    constexpr modint64& operator/=(const modint64& m) { return *this *= m.inv(); }
    constexpr modint64 operator+(const modint64& m) const { return modint64{*this} += m; }
    constexpr modint64 operator-(const modint64& m) const { return modint64{*this} -= m; }
    constexpr modint64 operator*(const modint64& m) const { return modint64{*this} *= m; }
    constexpr modint64 operator/(const modint64& m) const { return modint64{*this} /= m; }
    constexpr bool operator==(const modint64& m) const { return m_val == m(); }
    constexpr bool operator!=(const modint64& m) const { return not(*this == m); }
    friend std::istream& operator>>(std::istream& is, modint64& m)
    {
        ll v;
        return is >> v, m = v, is;
    }
    friend std::ostream& operator<<(std::ostream& os, const modint64& m) { return os << m(); }
    constexpr u64 get() const { return m_val; }
    constexpr u64 operator()() const { return m_val; }
    constexpr modint64 pow(u128 n) const
    {
        modint64 ans = 1;
        for (modint64 x = *this; n > 0; n >>= 1, x *= x) {
            if (n & 1) { ans *= x; }
        }
        return ans;
    }
    constexpr modint64 inv() const { return pow(mod - 2); }
    modint64 sinv() const { return sinv(m_val); }
    static modint64 fact(const uint n)
    {
        static std::vector<modint64> fs{1, 1};
        for (uint i = (uint)fs.size(); i <= n; i++) { fs.push_back(fs.back() * i); }
        return fs[n];
    }
    static modint64 ifact(const uint n)
    {
        static std::vector<modint64> ifs{1, 1};
        for (uint i = (uint)ifs.size(); i <= n; i++) { ifs.push_back(ifs.back() * sinv(i)); }
        return ifs[n];
    }
    static modint64 perm(const int n, const int k) { return k > n or k < 0 ? modint64{0} : fact(n) * ifact(n - k); }
    static modint64 comb(const int n, const int k) { return k > n or k < 0 ? modint64{0} : fact(n) * ifact(n - k) * ifact(k); }

private:
    static constexpr u64 norm(const u64 x) { return x < mod ? x : x - mod; }
    static constexpr u64 normll(const ll x) { return norm(u64(x % (ll)mod + (ll)mod)); }
    static modint64 sinv(const uint n)
    {
        static std::vector<modint64> is{1, 1};
        for (uint i = (uint)is.size(); i <= n; i++) { is.push_back(-is[mod % i] * (mod / i)); }
        return is[n];
    }
    u64 m_val;
};
