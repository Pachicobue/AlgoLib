#pragma once
#ifndef WITHOUT_STANDARD_LIBRARY
#    include <algorithm>
#    include <iostream>
#    include <vector>
#endif
template<typename SemiGroup>
class swag
{
    using T = typename SemiGroup::T;

public:
    swag() : m_merge{} {}
    void push_back(const T& x) { m_backs.push_back(x), m_Backs.push_back(m_Backs.empty() ? x : m_merge(m_Backs.back(), x)); }
    void push_front(const T& x) { m_fronts.push_back(x), m_Fronts.push_back(m_Fronts.empty() ? x : m_merge(x, m_Fronts.back())); }
    void pop_back()
    {
        if (m_Backs.empty()) {
            std::vector<T> as = m_fronts;
            m_fronts.clear(), m_Fronts.clear(), std::reverse(as.begin(), as.end());
            const int f = (int)as.size() / 2;
            for (int i = f - 1; i >= 0; i--) { m_fronts.push_back(as[i]); }
            for (int i = f; i + 1 < (int)as.size(); i++) { m_backs.push_back(as[i]); }
            calc();
        } else {
            m_backs.pop_back(), m_Backs.pop_back();
        }
    }
    void pop_front()
    {
        if (m_Fronts.empty()) {
            std::vector<T> as = m_backs;
            m_backs.clear(), m_Backs.clear();
            const int f = ((int)as.size() + 1) / 2;
            for (int i = f - 1; i >= 1; i--) { m_fronts.push_back(as[i]); }
            for (int i = f; i < (int)as.size(); i++) { m_backs.push_back(as[i]); }
            calc();
        } else {
            m_fronts.pop_back(), m_Fronts.pop_back();
        }
    }
    T fold() const { return m_fronts.empty() ? m_Backs.back() : m_backs.empty() ? m_Fronts.back() : m_merge(m_Fronts.back(), m_Backs.back()); }
    friend std::ostream& operator<<(std::ostream& os, const swag& sw)
    {
        std::vector<T> as = sw.fs;
        std::reverse(as.begin(), as.end());
        for (const T& b : sw.bs) { as.push_back(b); }
        os << "vs = [";
        for (const T& a : as) { os << a << ","; }
        return os << "]";
    }
    int size() const { return (int)m_fronts.size() + (int)m_backs.size(); }
    bool empty() const { return m_fronts.empty() and m_backs.empty(); }

private:
    void calc()
    {
        if (not m_fronts.empty()) {
            m_Fronts.push_back(m_fronts[0]);
            for (int i = 1; i < (int)m_fronts.size(); i++) { m_Fronts.push_back(m_merge(m_fronts[i], m_Fronts.back())); }
        }
        if (not m_backs.empty()) {
            m_Backs.push_back(m_backs[0]);
            for (int i = 1; i < (int)m_backs.size(); i++) { m_Backs.push_back(m_merge(m_Backs.back(), m_backs[i])); }
        }
    }
    std::vector<T> m_fronts, m_backs;
    std::vector<T> m_Fronts, m_Backs;
    SemiGroup m_merge;
};
