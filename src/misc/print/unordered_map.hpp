#pragma once
#include <iostream>
#include <unordered_map>
template<typename K, typename T, typename H, typename P, typename A>
std::ostream& operator<<(std::ostream& os, const std::unordered_map<K, T, H, P, A>& v)
{
    os << "[";
    for (const auto& e : v) { os << "<" << e.first << ": " << e.second << ">,"; }
    return (os << "]" << std::endl);
}
