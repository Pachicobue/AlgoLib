#pragma once
#ifndef WITHOUT_STANDARD_LIBRARY
#    include <cstdio>
#    include <cstring>
#    include <string>
#    include <vector>
#endif
class printer
{
public:
    printer()
    {
        for (int i = 0; i < 10000; i++) {
            for (int j = i, t = 3; t >= 0; t--, j /= 10) { m_dict[i * 4 + t] = (j % 10) + '0'; }
        }
    }
    ~printer() { flush(); }
    template<typename... Args> int ln(const Args&... args) { return dump(args...), put_char('\n'), 0; }
    template<typename... Args> int el(const Args&... args) { return dump(args...), put_char('\n'), flush(), 0; }

private:
    using ll  = long long;
    using ull = unsigned long long;
    static constexpr ull TEN(const int d) { return d == 0 ? 1ULL : TEN(d - 1) * 10ULL; }
    void flush() { fwrite(m_memory, 1, m_tail, stdout), m_tail = 0; }
    void put_char(const char c) { m_memory[m_tail++] = c; }
    static constexpr int dn(const ull x)
    {
        return x < TEN(10)
                   ? x < TEN(5)
                         ? x < TEN(2)
                               ? x < TEN(1) ? 1 : 2
                               : x < TEN(3) ? 3 : x < TEN(4) ? 4 : 5
                         : x < TEN(7)
                               ? x < TEN(6) ? 6 : 7
                               : x < TEN(8) ? 8 : x < TEN(9) ? 9 : 10
                   : x < TEN(14)
                         ? x < TEN(12)
                               ? x < TEN(11) ? 11 : 12
                               : x < TEN(13) ? 13 : 14
                         : x < TEN(16)
                               ? x < TEN(15) ? 15 : 16
                               : x < TEN(17) ? 17 : x < TEN(18) ? 18 : 19;
    }
    void dump(const char* s) { dump(std::string{s}); }
    void dump(const std::string& s)
    {
        for (const char c : s) { put_char(c); }
    }
    template<typename T>
    void dump(T v)
    {
        if (C - m_tail < 50) { flush(); }
        if (v < 0) { put_char('-'), v = -v; }
        const auto d = dn(v);
        int i        = d - 4;
        for (i = d - 4; i >= 0; i -= 4, v /= 10000) { memcpy(m_memory + m_tail + i, m_dict + (v % 10000) * 4, 4); }
        memcpy(m_memory + m_tail, m_dict + v * 4 - i, i + 4);
        m_tail += d;
    }
    template<typename T>
    void dump(const std::vector<T>& vs)
    {
        for (int i = 0; i < (int)vs.size(); i++) {
            if (i > 0) { put_char(' '); }
            dump(vs[i]);
        }
    }
    template<typename T>
    void dump(const std::vector<std::vector<T>>& vss)
    {
        for (int i = 0; i < (int)vss.size(); i++) {
            if (i > 0) { put_char('\n'); }
            dump(vss[i]);
        }
    }
    template<typename T, typename... Args> void dump(const T& v, const Args&... args) { return dump(v), put_char(' '), dump(args...), void(0); }

    static constexpr int C = 1 << 18;
    int m_tail             = 0;  // [0,m_tail)に出力データが入っている
    char m_memory[C];
    char m_dict[10000 * 4];  // 0000 0001 0002 ... 9999
} out;
