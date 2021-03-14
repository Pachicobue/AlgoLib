#pragma once
#ifndef WITHOUT_STANDARD_LIBRARY
#    include <array>
#    include <iostream>
#endif
template<typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& v)
{
    os << "[";
    for (const auto& e : v) { os << e << ","; }
    return (os << "]" << std::endl);
}
