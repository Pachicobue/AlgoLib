#pragma once
#include <map>
#include <vector>
template<typename T>
class zipper
{
public:
    int operator()(const T& val)
    {
        if (m_mp.count(val) == 0) {
            const int sz = m_mp.size();
            m_mp[val]    = sz;
        }
        return m_mp.at(val);
    }

private:
    std::map<T, int> m_mp;
};
