#pragma once
#ifndef WITHOUT_STANDARD_LIBRARY
#    include <algorithm>
#    include <cassert>
#    include <numeric>
#    include <vector>
#endif
#include "../misc/types.hpp"
template<int block_size>
class mo_iterator
{
public:
    mo_iterator(const std::vector<int>& xs_, const std::vector<int>& ys_) : xs{xs_}, ys{ys_}, is(xs.size())
    {
        std::iota(is.begin(), is.end(), 0);
        std::sort(is.begin(), is.end(), [&](int i, int j) {
            const int ib = xs[i] / block_size, jb = xs[j] / block_size;
            return ib != jb ? ib < jb : ys[i] < ys[j];
        });
    }
    template<typename R, typename L, typename D, typename U>
    int next(R right, L left, D down, U up)
    {
        assert(ii < (int)is.size());
        const int i = is[ii++], nx = xs[i], ny = ys[i];
        for (; x < nx; x++) { right(x, y); }
        for (; x > nx; x--) { left(x, y); }
        for (; y < ny; y++) { down(x, y); }
        for (; y > ny; y--) { up(x, y); }
        return i;
    }

private:
    int ii = 0, x = 0, y = 0;
    std::vector<int> xs, ys, is;
};
