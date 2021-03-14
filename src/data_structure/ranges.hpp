#pragma once
#ifndef WITHOUT_STANDARD_LIBRARY
#    include <iostream>
#    include <limits>
#    include <map>
#    include <type_traits>
#endif
template<typename T>
class ranges
{
public:
    static_assert(std::is_signed<T>::value, "Signed integer-type is required.");
    ranges() : m_rs{{std::numeric_limits<T>::min(), std::numeric_limits<T>::min() + 1}, {std::numeric_limits<T>::max() - 1, std::numeric_limits<T>::max()}} {}
    void insert(const T l, const T r)
    {
        auto lastit  = std::prev(m_rs.upper_bound(r));
        auto firstit = lastit;
        for (; firstit->second >= l; firstit--) {}
        firstit++;
        const T lmin = std::min(firstit->first, l), rmax   = std::max(lastit->second, r);
        m_rs.erase(firstit, std::next(lastit)), m_rs[lmin] = rmax;
    }
    void erase(const T l, const T r)
    {
        const auto lastit = std::prev(m_rs.upper_bound(r));
        auto firstit      = lastit;
        for (; firstit->second >= l; firstit--) {}
        firstit++;
        const T left = firstit->first, right = lastit->second;
        m_rs.erase(firstit, std::next(lastit));
        if (left < l) { insert(left, l); }
        if (r < right) { insert(r, right); }
    }
    std::pair<bool, std::pair<T, T>> support(const T x) const
    {
        const auto it = std::prev(m_rs.upper_bound(x));
        return {it->first <= x and it->second > x, *it};
    }
    const std::map<T, T>& data() const { return m_rs; }
    friend std::ostream& operator<<(std::ostream& os, const ranges& r)
    {
        os << "{ ";
        for (auto it = std::next(r.m_rs.begin()); it != std::prev(r.m_rs.end()); it++) { os << "[" << it->first << "," << it->second << "),"; }
        return os << " }";
    }

private:
    std::map<T, T> m_rs;
};
