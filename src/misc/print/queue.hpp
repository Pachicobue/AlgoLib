#pragma once
#include <iostream>
#include <queue>
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::queue<T1>& v)
{
    auto q = v;
    os << "[";
    while (not q.empty()) { os << q.front() << ",", q.pop(); }
    return os << "]\n";
}
