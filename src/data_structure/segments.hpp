#pragma once
#include <algorithm>
#include <vector>
#include "../misc/bit_ops.hpp"
class segments
{
private:
    using pii = std::pair<int, int>;
    const int ceil;
    std::vector<pii> segs;
    const int num;

public:
    segments(const int size) : ceil{(int)ceil2(size)}, segs(ceil << 1, pii{0, 0}), num{ceil << 1}
    {
        for (int sz = 1; sz <= ceil; sz <<= 1) {
            const int len = ceil / sz;
            for (int j = sz; j < (sz << 1); j++) { segs[j] = {len * (j - sz), len * (j - sz + 1)}; }
        }
    }
    std::vector<int> under(int l, int r) const
    {
        if (l >= r or r > ceil) { return std::vector<int>{}; }
        std::vector<int> linds, rinds;
        for (l += ceil, r += ceil; l < r; l >>= 1, r >>= 1) {
            if (l & 1) { linds.push_back(l++); }
            if (r & 1) { rinds.push_back(--r); }
        }
        for (; not rinds.empty(); rinds.pop_back()) { linds.push_back(rinds.back()); }
        return linds;
    }
    std::vector<int> over(const int a) const
    {
        if (a >= ceil) { return std::vector<int>{}; }
        std::vector<int> aboves;
        for (int i = a + ceil; i >= 1; i >>= 1) { aboves.push_back(i); }
        std::reverse(aboves.begin(), aboves.end());
        return aboves;
    }
    const pii& operator[](const int i) const { return segs[i]; }
    int size() const { return num; }
};
