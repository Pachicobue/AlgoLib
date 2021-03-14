#pragma once
#include <algorithm>
#include <vector>
template<typename T>
std::vector<T> divisors(const T n)
{
    std::vector<T> head, tail;
    for (T i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            head.push_back(i);
            if (i * i != n) { tail.push_back(n / i); }
        }
    }
    std::copy(tail.begin(), tail.end(), head.end());
    return head;
}
