#pragma once
#ifndef WITHOUT_STANDARD_LIBRARY
#    include <array>
#    include <cassert>
#    include <iostream>
#    include <vector>
#endif
#include "../misc/bit_ops.hpp"
template<int lg>
class wavelet
{
public:
    wavelet(std::vector<ull> vs) : sz{(int)vs.size()}
    {
        for (int i = 0; i < lg; i++) { zns[i] = 0, tables[i] = fid(sz); }
        std::vector<ull> z(sz), o(sz);
        int zn = 0, on = 0;
        for (int d = 0; d < lg; d++) {
            zn = 0, on = 0;
            for (int i = 0; i < sz; i++) {
                const bool b = btest(vs[i], lg - d - 1);
                tables[d].set(i, b), (b ? o[on++] : z[zn++]) = vs[i];
            }
            tables[d].build(), zns[d] = zn, std::swap(vs, z);
            for (int i = 0; i < on; i++) { vs[zn + i] = o[i]; }
        }
    }
    int less_than(int l, int r, const ull v) const
    {
        assert(l <= r);
        int ans = 0;
        for (int i = 0; i < lg; i++) {
            const int zl = tables[i].zero(l), zr = tables[i].zero(r), z = zns[i];
            if (btest(v, lg - i - 1)) {
                ans += zr - zl, l += z - zl, r += z - zr;
            } else {
                l = zl, r = zr;
            }
        }
        return ans;
    }
    int range_freq(const int l, const int r, const ull vmin, const ull vsup) const { return less_than(l, r, vsup) - less_than(l, r, vmin); }
    ull quantile(int l, int r, int n) const
    {
        assert(l <= r), assert(r - l > n);
        ull ans = 0;
        for (int i = 0; i < lg; i++) {
            const int zl = tables[i].zero(l), zr = tables[i].zero(r), z = zns[i];
            if (n >= zr - zl) {
                ans += ull(1) << (lg - i - 1), l += z - zl, r += z - zr, n -= (zr - zl);
            } else {
                l = zl, r = zr;
            }
        }
        return ans;
    }

private:
    static constexpr int bucket_size = sizeof(ull) * 8;
    static constexpr int bslog       = log2p1(bucket_size) - 1;
    static constexpr ull bcut(const ull n, const int l) { return (l == 0 ? 0ULL : (n << (64 - l) >> (64 - l))); }
    static constexpr int wind(const int n) { return n >> (bslog); }
    static constexpr int bind(const int n) { return bcut(n, bslog); }
    class fid
    {
    private:
        int sz, bn;
        std::vector<ull> datas;
        std::vector<int> larges;

    public:
        fid() : sz{0} {}
        fid(const int b) : sz{b}, bn{wind(sz) + 2}, datas(bn, 0), larges(bn, 0) {}
        void build()
        {
            for (int i = 1; i < (int)larges.size(); i++) { larges[i] = larges[i - 1] + popcount(datas[i - 1]); }
        }
        bool operator[](const int n) const { return btest(datas[wind(n)], bind(n)); }
        void set(const int n, const bool b) { datas[wind(n)] |= ull{b} << bind(n); }
        int one(const int n) const { return larges[wind(n)] + popcount(bcut(datas[wind(n)], bind(n))); }
        int zero(const int n) const { return n - one(n); }
    };
    const int sz;
    std::array<int, lg> zns;
    std::array<fid, lg> tables;
};
