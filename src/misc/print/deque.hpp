#pragma once
#ifndef WITHOUT_STANDARD_LIBRARY
#    include <deque>
#    include <iostream>
#endif
template<typename T, typename A>
std::ostream& operator<<(std::ostream& os, const std::deque<T, A>& v)
{
    os << "[";
    for (const auto& e : v) { os << e << ","; }
    return (os << "]" << std::endl);
}
