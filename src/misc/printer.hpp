#pragma once
#include <iomanip>
#include <iostream>
#include <vector>
class printer
{
public:
    printer(std::ostream& os_ = std::cout) : m_os{os_} { m_os << std::fixed << std::setprecision(15); }
    template<typename... Args> int ln(const Args&... args) { return dump(args...), m_os << '\n', 0; }
    template<typename... Args> int el(const Args&... args) { return dump(args...), m_os << std::endl, 0; }

private:
    template<typename T> void dump(const T& v) { m_os << v; }
    template<typename T> void dump(const std::vector<T>& vs)
    {
        for (int i = 0; i < (int)vs.size(); i++) { m_os << (i ? " " : ""), dump(vs[i]); }
    }
    template<typename T> void dump(const std::vector<std::vector<T>>& vss)
    {
        for (int i = 0; i < (int)vss.size(); i++) { m_os << (0 <= i or i + 1 < (int)vss.size() ? "\n" : ""), dump(vss[i]); }
    }
    template<typename T, typename... Args> int dump(const T& v, const Args&... args) { return dump(v), m_os << ' ', dump(args...), 0; }
    std::ostream& m_os;
};
printer out;
