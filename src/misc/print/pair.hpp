#pragma once
#include <iostream>
#include <utility>
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& v) { return (os << "<" << v.first << "," << v.second << ">"); }
