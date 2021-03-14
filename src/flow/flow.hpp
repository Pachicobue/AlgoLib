#pragma once
#ifndef WITHOUT_STANDARD_LIBRARY
#    include <iostream>
#    include <vector>
#endif
template<typename T>
struct flow
{
    using capacity_type = T;
    flow(const int v) : sz(v), edges(v) {}
    void add_edge(const int from, const int to, const capacity_type cap) { edges[from].push_back({to, (int)edges[to].size(), cap, false}), edges[to].push_back({from, (int)edges[from].size() - 1, 0, true}); }
    struct edge
    {
        int to, rev;
        capacity_type cap;
        const bool is_rev;
    };
    const std::vector<edge>& operator[](const int i) const { return edges[i]; }
    std::vector<edge>& operator[](const int i) { return edges[i]; }
    friend std::ostream& operator<<(std::ostream& os, const flow& f)
    {
        os << "[\n";
        for (int i = 0; i < f.size(); i++) {
            for (const auto& e : f[i]) {
                if (not e.is_rev) { os << i << "->" << e.to << ":"
                                       << e.cap << "\n"; }
            }
        }
        return (os << "]\n");
    }
    int size() const { return sz; }

private:
    const int sz;
    std::vector<std::vector<edge>> edges;
};
