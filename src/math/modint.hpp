#pragma once
#include <iostream>
#include <vector>
#include "../misc/types.hpp"
struct modinfo
{
    void set_mod(const uint nmod) { mod = nmod; }
    uint mod, root, max2p;
};
template<const modinfo& info>
class modint
{
public:
    static constexpr const uint& mod   = info.mod;
    static constexpr const uint& root  = info.root;
    static constexpr const uint& max2p = info.max2p;

    constexpr modint() : m_val{0} {}
    constexpr modint(const ll v) : m_val{normll(v)} {}
    constexpr void set_raw(const uint v) { m_val = v; }
    constexpr modint operator-() const { return modint{0} - (*this); }
    constexpr modint& operator+=(const modint& m) { return m_val = norm(m_val + m()), *this; }
    constexpr modint& operator-=(const modint& m) { return m_val = norm(m_val + mod - m()), *this; }
    constexpr modint& operator*=(const modint& m) { return m_val = normll((ll)m_val * (ll)m() % (ll)mod), *this; }
    constexpr modint& operator/=(const modint& m) { return *this *= m.inv(); }
    constexpr modint operator+(const modint& m) const { return modint{*this} += m; }
    constexpr modint operator-(const modint& m) const { return modint{*this} -= m; }
    constexpr modint operator*(const modint& m) const { return modint{*this} *= m; }
    constexpr modint operator/(const modint& m) const { return modint{*this} /= m; }
    constexpr bool operator==(const modint& m) const { return m_val == m(); }
    constexpr bool operator!=(const modint& m) const { return not(*this == m); }
    friend std::istream& operator>>(std::istream& is, modint& m)
    {
        ll v;
        return is >> v, m = v, is;
    }
    friend std::ostream& operator<<(std::ostream& os, const modint& m) { return os << m(); }
    constexpr uint get() const { return m_val; }
    constexpr uint operator()() const { return m_val; }
    constexpr modint pow(ull n) const
    {
        modint ans = 1;
        for (modint x = *this; n > 0; n >>= 1, x *= x) {
            if (n & 1ULL) { ans *= x; }
        }
        return ans;
    }
    constexpr modint inv() const { return pow(mod - 2); }
    static modint sinv(const uint n)
    {
        static std::vector<modint> is{1, 1};
        for (uint i = (uint)is.size(); i <= n; i++) { is.push_back(-is[mod % i] * (mod / i)); }
        return is[n];
    }
    static modint fact(const uint n)
    {
        static std::vector<modint> fs{1, 1};
        for (uint i = (uint)fs.size(); i <= n; i++) { fs.push_back(fs.back() * i); }
        return fs[n];
    }
    static modint ifact(const uint n)
    {
        static std::vector<modint> ifs{1, 1};
        for (uint i = (uint)ifs.size(); i <= n; i++) { ifs.push_back(ifs.back() * sinv(i)); }
        return ifs[n];
    }
    static modint comb(const int n, const int k) { return k > n or k < 0 ? modint{0} : fact(n) * ifact(n - k) * ifact(k); }

private:
    static constexpr uint norm(const uint x) { return x < mod ? x : x - mod; }
    static constexpr uint normll(const ll x) { return norm(uint(x % (ll)mod + (ll)mod)); }
    uint m_val;
};
constexpr modinfo modinfo_1000000007 = {1000000007, 5, 1};
constexpr modinfo modinfo_998244353  = {998244353, 3, 23};
using modint_1000000007              = modint<modinfo_1000000007>;
using modint_998244353               = modint<modinfo_998244353>;
