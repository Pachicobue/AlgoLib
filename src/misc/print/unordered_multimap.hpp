#pragma once
#ifndef WITHOUT_STANDARD_LIBRARY
#    include <iostream>
#    include <unordered_map>
#endif
template<typename K, typename T, typename H, typename P, typename A>
std::ostream& operator<<(std::ostream& os, const std::unordered_multimap<K, T, H, P, A>& v)
{
    os << "[";
    for (const auto& e : v) { os << "<" << e.first << ": " << e.second << ">,"; }
    return (os << "]" << std::endl);
}
