#pragma once
#ifndef WITHOUT_STANDARD_LIBRARY
#    include <iostream>
#    include <vector>
#endif
template<typename T, typename A>
std::ostream& operator<<(std::ostream& os, const std::vector<T, A>& v)
{
    os << "[";
    for (const auto& e : v) { os << e << ","; }
    return (os << "]" << std::endl);
}
