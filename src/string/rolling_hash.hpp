#pragma once
#include <vector>
#include "../misc/random.hpp"
#include "../misc/types.hpp"
class rolling_hash
{
public:
    template<typename InIt>
    rolling_hash(const InIt first, const InIt last, const ull base_  // = rng64((ull)2, mask61 - 1)
                 ) : sz(std::distance(first, last)), pow(sz + 1, 1), h(sz + 1, 0), base{base_}
    {
        for (int i = 1; i <= sz; i++) { pow[i] = mod(mul(pow[i - 1], base)), h[i] = mod(mul(h[i - 1], base) + *std::next(first, i - 1)); }
    }
    ull operator()(const int l, const int r) const { return mod(h[r] + offset - mul(h[l], pow[r - l])); }
    template<typename C>
    void push_back(const C c)
    {
        sz++;
        pow.push_back(mod(mul(pow.back(), base)));
        h.push_back(mod(mul(h.back(), base) + c));
    }

private:
    static constexpr ull mask30 = ((ull)1 << 30) - 1;
    static constexpr ull mask31 = ((ull)1 << 31) - 1;
    static constexpr ull mask61 = ((ull)1 << 61) - 1;
    static constexpr ull offset = mask61 * 7;
    static constexpr ull mod(const ull x)
    {
        const ull y = (x >> 61) + (x & mask61);
        return y >= mask61 ? y - mask61 : y;
    }
    static constexpr ull mul(const ull x, const ull y)
    {
        const ull xh = x >> 31, xl = x & mask31;
        const ull yh = y >> 31, yl = y & mask31;
        const ull z  = xl * yh + xh * yl;
        const ull zh = z >> 30, zl = z & mask30;
        return xh * yh * 2 + zh + (zl << 31) + xl * yl;
    }
    int sz;
    std::vector<ull> pow, h;
    ull base;
};
