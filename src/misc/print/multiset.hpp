#pragma once
#include <iostream>
#include <set>
template<typename T, typename C, typename A>
std::ostream& operator<<(std::ostream& os, const std::multiset<T, C, A>& v)
{
    os << "[";
    for (const auto& e : v) { os << e << ","; }
    return (os << "]" << std::endl);
}
