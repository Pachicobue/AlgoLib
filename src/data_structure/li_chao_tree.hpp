#pragma once
#include <iostream>
#include <limits>
#include <tuple>
#include <vector>
template<typename T, typename V = T>
class li_chao_tree
{
    using L                = std::pair<T, T>;
    using P                = std::pair<T, T>;
    using Node             = std::pair<L, std::pair<int, int>>;
    static constexpr L nil = L{T{}, std::numeric_limits<T>::max()};
    static bool comp(const L& l1, const L& l2, const T x) { return V(l1.first) * V(x) + V(l1.second) < V(l2.first) * V(x) + V(l2.second); }

public:
    li_chao_tree(const T xmin, const T xsup) : m_xmin{xmin}, m_xsup{xsup}, m_nodes{{nil, {-1, -1}}} {}
    void add_line(const T a, const T b) { add(L{a, b}, 0, m_xmin, m_xsup); }
    void add_seg(const T a, const T b, const T xl, const T xr)
    {
        auto dfs = [&](auto self, const int ind, const T left, const T right) -> void {
            if (xl <= left and right <= xr) {
                add(L{a, b}, ind, left, right);
            } else {
                auto [lc, rc] = m_nodes[ind].second;
                if (right - left == 1) { return; }
                const T mid = (left + right) / T{2};
                if (left < xr and xl < mid) {
                    if (lc == -1) { lc = m_nodes[ind].second.first = alloc(); }
                    self(self, lc, left, mid);
                }
                if (mid < xr and xl < right) {
                    if (rc == -1) { rc = m_nodes[ind].second.second = alloc(); }
                    self(self, rc, mid, right);
                }
            }
        };
        dfs(dfs, 0, m_xmin, m_xsup);
    }
    L min_line(const T x) const
    {
        T left = m_xmin, right = m_xsup;
        L minl = nil;
        for (int ind = 0; ind != -1;) {
            const auto& pl = m_nodes[ind].first;
            if (comp(pl, minl, x)) { minl = pl; }
            const auto [lc, rc]   = m_nodes[ind].second;
            const T mid           = (right + left) / 2;
            std::tie(left, right) = (x < mid ? P{left, mid} : P{mid, right});
            ind                   = (x < mid ? lc : rc);
        }
        return minl;
    }
    bool exist(const T x) const
    {
        T left = m_xmin, right = m_xsup;
        for (int ind = 0; ind != -1;) {
            if (m_nodes[ind].first != nil) { return true; }
            const auto [lc, rc]   = m_nodes[ind].second;
            const T mid           = (right + left) / 2;
            std::tie(left, right) = (x < mid ? P{left, mid} : P{mid, right});
            ind                   = (x < mid ? lc : rc);
        }
        return false;
    }

private:
    void add(L l, int ind, T left, T right)
    {
        for (;;) {
            const auto& pl      = m_nodes[ind].first;
            const auto [lc, rc] = m_nodes[ind].second;
            const T mid         = (left + right) / T{2};
            const bool lunder = comp(l, pl, left), runder = comp(l, pl, right), munder = comp(l, pl, mid);
            if (munder) { std::swap(l, m_nodes[ind].first); }
            if (lunder == runder) { break; }
            int nind = (lunder == munder ? rc : lc);
            if (nind == -1) { nind = (lunder == munder ? m_nodes[ind].second.second : m_nodes[ind].second.first) = alloc(); }
            ind = nind;
            if (right - left == 1) { break; }
            std::tie(left, right) = (lunder == munder ? P{mid, right} : P{left, mid});
        }
    }
    int alloc() { return m_nodes.push_back({nil, {-1, -1}}), m_nodes.size() - 1; }
    T m_xmin, m_xsup;
    std::vector<Node> m_nodes;
};
