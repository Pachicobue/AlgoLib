#pragma once
#include <algorithm>
#include <cassert>
#include <vector>
#include "../misc/bit_ops.hpp"
#include "../misc/range.hpp"
#include "modint.hpp"

template<typename mint>
class fps : public std::vector<mint>
{
public:
    using std::vector<mint>::vector;
    using std::vector<mint>::resize;
    fps(const std::vector<mint>& vs) : std::vector<mint>{vs} {}
    int size() const { return std::vector<mint>::size(); }
    int deg() const { return size() - 1; }
    fps low(const int n) const { return fps{this->begin(), this->begin() + std::min(n, size())}; }
    fps rev() const
    {
        fps ans = *this;
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
    mint eval(const mint& x) const
    {
        mint ans   = 0;
        mint power = 1;
        for (int i = 0; i < size(); i++, power *= x) { ans += power * (*this)[i]; }
        return ans;
    }
    mint& operator[](const int n)
    {
        if (size() < n + 1) { resize(n + 1); }
        return std::vector<mint>::operator[](n);
    }
    const mint& operator[](const int n) const { return std::vector<mint>::operator[](n); }
    mint at(const int n) const { return (n < size() ? (*this)[n] : mint{0}); }
    fps operator-() const
    {
        fps ans = *this;
        for (auto& v : ans) { v = -v; }
        return ans;
    }
    fps& operator+=(const fps& f)
    {
        for (int i = 0; i < f.size(); i++) { (*this)[i] += f[i]; }
        return *this;
    }
    fps& operator-=(const fps& f)
    {
        for (int i = 0; i < f.size(); i++) { (*this)[i] -= f[i]; }
        return *this;
    }
    fps& operator*=(const fps& f) { return (*this) = (*this) * f; }
    fps& operator<<=(const int s) { return *this = (*this << s); }
    fps& operator>>=(const int s) { return *this = (*this >> s); }
    fps operator+(const fps& f) const { return fps(*this) += f; }
    fps operator-(const fps& f) const { return fps(*this) -= f; }
    fps operator*(const fps& f) const { return mult(f, size() + f.size() - 1); }
    fps operator<<(const int s) const
    {
        fps ans(size() + s);
        for (int i = 0; i < size(); i++) { ans[i + s] = (*this)[i]; }
        return ans;
    }
    fps operator>>(const int s) const
    {
        fps ans;
        for (int i = s; i < size(); i++) { ans[i - s] = (*this)[i]; }
        return ans;
    }
    friend std::ostream& operator<<(std::ostream& os, const fps& f) { return os << static_cast<std::vector<mint>>(f); }

    fps derivative() const
    {
        fps ans;
        for (int i = 1; i < size(); i++) { ans[i - 1] = (*this)[i] * i; }
        return ans;
    }
    fps integral() const
    {
        fps ans;
        for (int i = 1; i <= size(); i++) { ans[i] = (*this)[i - 1] * mint::sinv(i); }
        return ans;
    }
    fps mult(const fps& f, const int sz) const
    {
        if (sz == 0) { return fps{}; }
        const int N = std::min(size(), sz) + std::min(f.size(), sz) - 1;
        if (N <= 16) {
            fps ans(sz);
            for (int i = 0; i < std::min(size(), sz); i++) {
                for (int j = 0; j < f.size() and i + j < sz; j++) { ans[i + j] += (*this)[i] * f[j]; }
            }
            return ans;
        } else if (N <= (1 << mint::max2p)) {
            auto ans = conv<mint>(*this, f, sz);
            return ans;
        } else {
            const auto cs1 = conv<submint1>(*this, f, sz);
            const auto cs2 = conv<submint2>(*this, f, sz);
            const auto cs3 = conv<submint3>(*this, f, sz);
            fps ans((int)cs1.size());
            for (int i = 0; i < (int)cs1.size(); i++) { ans[i] = restore(cs1[i](), cs2[i](), cs3[i]()); }
            return ans;
        }
    }
    fps smult(const int p, const mint a, const int sz)  // *(1+ax^p) (mod x^sz)
    {
        fps ans = low(sz);
        for (int i = 0; i + p < sz; i++) { ans[i + p] += (*this)[i] * a; }
        return ans;
    }
    fps sdiv(const int p, const mint a, const int sz)  // *(1+ax^p)^(-1) (mod x^sz)
    {
        fps ans = low(sz);
        for (int i = 0; i + p < sz; i++) { ans[i + p] -= ans[i] * a; }
        return ans;
    }
    fps inv(const int sz) const
    {
        const int n = size();
        assert((*this)[0]() != 0);
        const int N = n * 2 - 1;
        if (N <= (1 << mint::max2p)) {
            fps r{(*this)[0].inv()};
            for (int lg = 0, m = 1; m < sz; m <<= 1, lg++) {
                fps f{this->begin(), this->begin() + std::min(n, 2 * m)};
                fps g = r;
                f.resize(2 * m), g.resize(2 * m);
                trans(f, lg + 1, false), trans(g, lg + 1, false);
                for (int i = 0; i < 2 * m; i++) { f[i] *= g[i]; }
                trans(f, lg + 1, true);
                std::fill(f.begin(), f.begin() + m, 0);
                trans(f, lg + 1, false);
                for (int i = 0; i < 2 * m; i++) { f[i] *= g[i]; }
                trans(f, lg + 1, true);
                for (int i = m; i < std::min(2 * m, sz); i++) { r[i] = -f[i]; }
            }
            return r;
        } else {
            fps g{(*this)[0].inv()};
            for (int lg = 0, m = 1; m < sz; m <<= 1, lg++) { g = fps{2} * g - this->mult(g.mult(g, 2 * m), 2 * m); }
            return g.low(sz);
        }
    }
    fps log(const int sz) const
    {
        assert((*this)[0]() == 1);
        auto ans = derivative().mult(inv(sz), sz).integral();
        ans.resize(sz);
        return ans;
    }
    fps exp(const int sz) const
    {
        const int l = lsb(sz);
        if (l == -1) { return fps{1}.low(sz); }
        assert((*this)[0]() == 0);

        const int n = size();
        const int N = n * 2 - 1;
        if (N <= (1 << mint::max2p)) {
            fps f = {1, (*this)[1]}, g{1}, G{1, 1};
            for (int m = 2, lg = 1; m < sz; m <<= 1, lg++) {
                auto F = f;
                F.resize(2 * m), trans(F, lg + 1, false);
                fps z(m);
                for (int i = 0; i < m; i++) { z[i] = F[i] * G[i]; }
                trans(z, lg, true);
                std::fill(z.begin(), z.begin() + m / 2, 0);
                trans(z, lg, false);
                for (int i = 0; i < m; i++) { z[i] *= G[i]; }
                trans(z, lg, true);
                for (int i = m / 2; i < m; i++) { g[i] = -z[i]; }
                G      = g, G.resize(m * 2), trans(G, lg + 1, false);
                auto q = low(m).derivative();
                q.resize(m), trans(q, lg, false);
                for (int i = 0; i < m; i++) { q[i] *= F[i]; }
                trans(q, lg, true);
                const auto df = f.derivative();
                for (int i = 0; i < m - 1; i++) { q[i] -= df[i]; }
                q.resize(m * 2);
                for (int i = 0; i < m - 1; i++) { q[m + i] = q[i], q[i] = 0; }
                trans(q, lg + 1, false);
                for (int i = 0; i < m * 2; i++) { q[i] *= G[i]; }
                trans(q, lg + 1, true), q.pop_back(), q = q.integral();
                for (int i = m; i < std::min(size(), m * 2); i++) { q[i] += (*this)[i]; }
                std::fill(q.begin(), q.begin() + m, 0), trans(q, lg + 1, false);
                for (int i = 0; i < m * 2; i++) { q[i] *= F[i]; }
                trans(q, lg + 1, true);
                for (int i = m; i < 2 * m; i++) { f[i] = q[i]; }
            }
            return f.low(sz);
        } else {
            fps f{1};
            for (int m = 1; m < sz; m <<= 1) {
                auto g = low(2 * m);
                g[0] += 1;
                f.resize(2 * m);
                g -= f.log(2 * m);
                g = f.mult(g, 2 * m);
                for (int i = m; i < std::min(2 * m, g.size()); i++) { f[i] = g[i]; }
            }
            return f.low(sz);
        }
    }
    fps pow(const int n, int sz = -1) const
    {
        if (sz == -1) { sz = deg() * n + 1; }
        if (n == 0) { return fps{1}.low(sz); }
        if (size() == 0) { return fps{}; }
        const int p = lsb((size() - 1) / n);
        if (p == -1) { return fps{}; }
        const mint a = (*this)[p];
        fps f        = (*this) >> p;
        for (auto& c : f) { c /= a; }
        f = f.log(sz - p * n);
        for (auto& c : f) { c *= n; }
        f = f.exp(sz - p * n);
        fps g;
        for (int i = 0; i < f.size(); i++) { g[i + p * n] = f[i] * a.pow(n); }
        return g;
    }
    fps tshift(const mint c) const
    {
        const int N = size();
        fps f(N), d(N);
        for (int i = 0; i < N; i++) { d[i] = c.pow(N - 1 - i) * mint::ifact(N - 1 - i); }
        for (int i = 0; i < N; i++) { f[i] = (*this)[i] * mint::fact(i); }
        f = f * d;
        fps g(N);
        for (int i = 0; i < N; i++) { g[i] = f[i + N - 1] * mint::ifact(i); }
        return g;
    }
    fps quot(const fps& g) const
    {
        const int N = size(), M = g.size();
        if (N < M) { return fps{}; }
        const auto fR = rev(), gR = g.rev();
        return fR.mult(gR.inv(N - M + 1), N - M + 1).rev();
    }
    fps rem(const fps& g) const { return (*this) - g * quot(g); }

private:
    int lsb(int sz = -1) const
    {
        if (sz == -1) { sz = size() - 1; }
        for (int p = 0; p <= sz; p++) {
            if ((*this)[p]() != 0) { return p; }
        }
        return -1;
    }

    static constexpr modinfo info1 = {469762049, 3, 26};
    static constexpr modinfo info2 = {167772161, 3, 25};
    static constexpr modinfo info3 = {754974721, 11, 24};
    using submint1                 = modint<info1>;
    using submint2                 = modint<info2>;
    using submint3                 = modint<info3>;
    template<typename submint>
    static void trans(std::vector<submint>& as, const int lg, const bool rev)
    {
        const int N = 1 << lg;
        assert((int)as.size() == N);
        std::vector<submint> rs, irs;
        if (rs.empty()) {
            const submint r = submint(submint::root), ir = r.inv();
            rs.resize(submint::max2p + 1), irs.resize(submint::max2p + 1);
            rs.back() = -r.pow((submint::mod - 1) >> submint::max2p), irs.back() = -ir.pow((submint::mod - 1) >> submint::max2p);
            for (uint i = submint::max2p; i >= 1; i--) { rs[i - 1] = -(rs[i] * rs[i]), irs[i - 1] = -(irs[i] * irs[i]); }
        }
        const auto drange = (rev ? range(0, lg, 1) : range(lg - 1, -1, -1));
        for (const int d : drange) {
            const int width = 1 << d;
            submint e       = 1;
            for (int i = 0, j = 1; i < N; i += width * 2, j++) {
                for (int l = i, r = i + width; l < i + width; l++, r++) {
                    const submint x = as[l], y = (rev ? as[r] : as[r] * e);
                    as[l] = x + y, as[r] = (rev ? (x - y) * e : x - y);
                }
                e *= (rev ? irs : rs)[lsbp1(j) + 1];
            }
        }
        if (rev) {
            const submint iN = submint{N}.inv();
            for (auto& a : as) { a *= iN; }
        }
    }
    template<typename submint>
    static std::vector<submint> conv(const std::vector<mint>& as, const std::vector<mint>& bs, const int sz)
    {
        const int M = std::min((int)as.size(), sz) + std::min((int)bs.size(), sz) - 1, lg = clog(M);
        const int L = 1 << lg;
        std::vector<submint> As(L), Bs(L);
        for (int i = 0; i < std::min((int)as.size(), sz); i++) { As[i] = as[i](); }
        for (int i = 0; i < std::min((int)bs.size(), sz); i++) { Bs[i] = bs[i](); }
        trans(As, lg, false), trans(Bs, lg, false);
        for (int i = 0; i < L; i++) { As[i] *= Bs[i]; }
        trans(As, lg, true);
        const int N = std::min(sz, (int)as.size() + (int)bs.size() - 1);
        As.resize(N);
        return As;
    }
    static constexpr submint2 ip1   = submint2{submint1::mod}.inv();
    static constexpr submint3 ip2   = submint3{submint2::mod}.inv();
    static constexpr submint3 ip1p2 = submint3{submint1::mod}.inv() * submint3{submint2::mod}.inv();
    static constexpr mint p1        = mint{submint1::mod};
    static constexpr mint p1p2      = mint{submint1::mod} * mint{submint2::mod};
    static constexpr mint restore(const int x1, const int x2, const int x3)
    {
        const int k0 = x1, k1 = (ip1 * (x2 - k0))(), k2 = (ip1p2 * (x3 - k0) - ip2 * k1)();
        return p1p2 * k2 + p1 * k1 + k0;
    }
};
