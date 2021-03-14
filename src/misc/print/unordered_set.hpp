#pragma once
#ifndef WITHOUT_STANDARD_LIBRARY
#    include <iostream>
#    include <unordered_set>
#endif
template<typename T, typename H, typename P, typename A>
std::ostream& operator<<(std::ostream& os, const std::unordered_set<T, H, P, A>& v)
{
    os << "[";
    for (const auto& e : v) { os << e << ","; }
    return (os << "]" << std::endl);
}
