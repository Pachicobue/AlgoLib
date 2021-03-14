#pragma once
#ifndef WITHOUT_STANDARD_LIBRARY
#    include <iostream>
#    include <tuple>
#    include <vector>
#endif
class scanner
{
public:
    scanner(std::istream& is_ = std::cin) : m_is{is_} { m_is.tie(nullptr), std::ios::sync_with_stdio(false); }
    template<typename T> T val()
    {
        T v;
        return m_is >> v, v;
    }
    template<typename T> T val(const T offset) { return val<T>() - offset; }
    template<typename T> std::vector<T> vec(const int n)
    {
        return make_v<T>(n, [this]() { return val<T>(); });
    }
    template<typename T> std::vector<T> vec(const int n, const T offset)
    {
        return make_v<T>(n, [this, offset]() { return val<T>(offset); });
    }
    template<typename T> std::vector<std::vector<T>> vvec(const int n0, const int n1)
    {
        return make_v<std::vector<T>>(n0, [this, n1]() { return vec<T>(n1); });
    }
    template<typename T> std::vector<std::vector<T>> vvec(const int n0, const int n1, const T offset)
    {
        return make_v<std::vector<T>>(n0, [this, n1, offset]() { return vec<T>(n1, offset); });
    }
    template<typename... Args> auto tup() { return std::tuple<std::decay_t<Args>...>{val<Args>()...}; }
    template<typename... Args> auto tup(const Args&... offsets) { return std::tuple<std::decay_t<Args>...>{val<Args>(offsets)...}; }

private:
    template<typename T, typename F>
    std::vector<T> make_v(const int n, F f)
    {
        std::vector<T> ans;
        for (int i = 0; i < n; i++) { ans.push_back(f()); }
        return ans;
    }
    std::istream& m_is;
};
scanner in;
