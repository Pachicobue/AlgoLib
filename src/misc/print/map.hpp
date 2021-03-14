#pragma once
#include <iostream>
#include <map>
template<typename K, typename T, typename C, typename A>
std::ostream& operator<<(std::ostream& os, const std::map<K, T, C, A>& v)
{
    os << "[";
    for (const auto& e : v) { os << "<" << e.first << ": " << e.second << ">,"; }
    return (os << "]" << std::endl);
}
