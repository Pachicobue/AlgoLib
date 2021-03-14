#pragma once
#include <vector>

template<typename T>
class rbstree
{
    using uint = unsigned int;
    struct Node
    {
        T val;
        int sz = 0;
        int pi = -1, li = -1, ri = -1;
    };
    static uint xrand()
    {
        static uint x = 123456789, y = 362436069, z = 521288629, w = 88675123;
        const uint t = (x ^ (x << 11));
        x = y, y = z, z = w;
        return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
    }

public:
    rbstree() {}
    const Node& operator[](const int r) const { return nodes[r]; }
    Node& operator[](const int r) { return nodes[r]; }
    int get(const int r, const int k)
    {
        const auto [lr, R]  = split(r, k);
        const auto [mr, rr] = split(R, 1);
        return mr;
    }
    int merge(const int ri, const int rj)
    {
        if (ri == -1 or rj == -1) { return ri == -1 ? rj : ri; }
        if (xrand() % (uint)(size(ri) + size(rj)) < (uint)size(ri)) {
            const int rr        = merge(nodes[ri].ri, rj);
            return nodes[ri].ri = rr, nodes[rr].pi = ri, up(ri);
        } else {
            const int lr        = merge(nodes[rj].li, ri);
            return nodes[rj].li = lr, nodes[lr].pi = rj, up(rj);
        }
    }
    std::pair<int, int> split(const int r, const int k)
    {
        const int li = nodes[r].li, ri = nodes[r].ri;
        if (size(r) == 0) { return {-1, -1}; }
        if (size(li) >= k) {
            const auto ans = split(li, k);
            const int lr   = ans.second;
            nodes[r].li = lr, nodes[lr].pi = r, up(r);
            return std::make_pair(ans.first, r);
        } else {
            const auto ans = split(ri, k - size(li) - 1);
            const int rr   = ans.first;
            nodes[r].ri = rr, nodes[rr].pi = r, up(r);
            return std::make_pair(r, ans.second);
        }
    }
    int alloc(const T v) { return nodes.emplace_back(v, 1, -1, -1, -1), nodes.size() - 1; }
    int size(const int r) const { return r == -1 ? 0 : nodes[r].sz; }
    std::vector<Node> dump(const int r) const
    {
        if (r == -1) { return std::vector<Node>{}; }
        const auto lv         = dump(nodes[r].li);
        const auto rv         = dump(nodes[r].ri);
        std::vector<Node> ans = lv;
        ans.push_back(nodes[r]);
        for (const auto& v : rv) { ans.push_back(v); }
        return ans;
    }

private:
    int is_right(const int i) { return nodes[i].pi != -1 and nodes[nodes[i].pi].ri == i; }
    int is_left(const int i) { return nodes[i].pi != -1 and nodes[nodes[i].pi].li == i; }
    int up(const int i) { return nodes[i].sz = size(nodes[i].left) + size(nodes[i].right) + 1, i; }
    std::vector<Node> nodes;
};
