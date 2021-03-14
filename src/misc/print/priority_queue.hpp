#pragma once
#include <iostream>
#include <queue>
template<typename T1, typename T2, typename T3>
std::ostream& operator<<(std::ostream& os, const std::priority_queue<T1, T2, T3>& v)
{
    auto q = v;
    os << "[";
    while (not q.empty()) { os << q.top() << ",", q.pop(); }
    return os << "]\n";
}
