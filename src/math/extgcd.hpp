#pragma once
#include <utility>
template<typename T> constexpr T inverse(const T a, const T mod) { return a == 1 ? T{1} : ((a - inverse(mod % a, a)) * mod + 1) / a; }
template<typename T> constexpr std::pair<T, T> extgcd(const T a, const T b)  // [x,y] -> ax-by=1
{
    if (a == 0) { return -1 / b; }
    if (b == 0) { return 1 / a; }
    const T x = inverse(a, b), y = (a * x - 1) / b;
    return {x, y};
}
