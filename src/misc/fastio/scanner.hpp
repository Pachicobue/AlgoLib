#pragma once
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <tuple>
#include <vector>
class scanner
{
public:
    scanner() {}
    template<typename T>
    T val()
    {
        if (m_tail - m_head < 40) { disk_read(); }
        char c         = get_char();
        const bool neg = (c == '-');
        if (neg) { c = get_char(); }
        T ans = 0;
        while (c >= '0') {
            ans = ans * T{10} + (c - '0');
            c   = get_char();
        }
        return (neg ? -ans : ans);
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
    char get_char() { return m_memory[m_head++]; }
    void disk_read()
    {
        std::copy(m_memory + m_head, m_memory + m_tail, m_memory);
        m_tail -= m_head, m_head = 0;
        m_tail += fread(m_memory + m_tail, 1, C - m_tail, stdin);  // stdinからドカッと読み込む
    }

    static constexpr int C = 1 << 18;
    int m_head = 0, m_tail = 0;  // [m_head,m_tail)に文字列が入っている
    char m_memory[C];
} in;
