#pragma once
#include <vector>
template<typename T, int n, int i = 0>
auto nd_array(int const (&szs)[n], const T x = T{})
{
    if constexpr (i == n) {
        return x;
    } else {
        return std::vector(szs[i], nd_array<T, n, i + 1>(szs, x));
    }
}
