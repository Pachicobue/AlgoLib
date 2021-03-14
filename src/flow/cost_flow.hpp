#pragma once
#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>
#include "../misc/constants.hpp"
template<typename Cap, typename Cost>
struct cost_flow
{
private:
    struct edge
    {
        int to, rev;
        Cap cap;
        Cost cost;
        const bool is_rev;
    };
    const int sz;
    std::vector<std::vector<edge>> edges;
    std::vector<Cost> pot;

public:
    cost_flow(const int v) : sz(v), edges(v), pot(v, 0) {}
    void add_edge(const int from, const int to, const Cap cap, const Cost cost) { assert(from < sz), assert(to < sz), edges[from].push_back(edge{to, edges[to].size(), cap, cost, false}), edges[to].push_back(edge{from, static_cast<int>(edges[from].size() - 1), 0, -cost, true}); }
    const std::vector<edge>& operator[](const int i) const { return assert(i < sz), edges[i]; }
    std::vector<edge>& operator[](const int i) { return assert(i < sz), edges[i]; }
    void calc_potential(const int s, const bool is_dag = false)
    {
        if (is_dag) {
            std::vector<int> ord;
            std::vector<bool> used(sz, 0);
            auto dfs = [&](auto&& self, const int s) -> void {
                if (not used[s]) {
                    used[s] = true;
                    for (const auto& e : edges[s]) {
                        if (e.cap == 0) { continue; }
                        self(self, e.to);
                    }
                    ord.push_back(s);
                }
            };
            for (int i = 0; i < sz; i++) { dfs(dfs, i); }
            std::reverse(ord.begin(), ord.end());
            std::fill(pot.begin(), pot.end(), inf_v<Cost>);
            for (int i = 0; i < sz; i++) {
                if (ord[i] == s) { pot[s] = 0; }
                if (pot[ord[i]] == inf_v<Cost>) { continue; }
                for (const auto& e : edges[ord[i]]) {
                    if (e.cap == 0) { continue; }
                    pot[e.to] = std::min(pot[e.to], pot[ord[i]] + e.cost);
                }
            }
        } else {
            std::fill(pot.begin(), pot.end(), inf_v<Cost>);
            pot[s] = 0;
            for (int i = 0; i < sz; i++) {
                for (int v = 0; v < sz; v++) {
                    if (pot[v] == inf_v<Cost>) { continue; }
                    for (const auto& e : edges[v]) {
                        if (e.cap == 0) { continue; }
                        if (pot[e.to] <= pot[v] + e.cost) { continue; }
                        pot[e.to] = pot[v] + e.cost;
                        if (i + 1 == sz) { pot[e.to] = -inf_v<Cost>; }
                    }
                }
            }
        }
    }
    template<typename Result>
    std::pair<bool, Result> primal_dual(const int s, const int t, Cap f)
    {
        std::vector<Cost> dist(sz, inf_v<Cost>);
        using P = std::pair<Result, int>;
        std::priority_queue<P, std::vector<P>, std::greater<P>> q;
        std::vector<int> prev_v(sz), prev_e(sz);
        Result ans = 0;
        while (f > 0) {
            std::fill(dist.begin(), dist.end(), inf_v<Cost>);
            dist[s] = 0, q.push({0, s});
            while (not q.empty()) {
                const Result cost = q.top().first;
                const int v       = q.top().second;
                q.pop();
                if (dist[v] < cost) { continue; }
                for (int i = 0; i < edges[v].size(); i++) {
                    const auto& e = edges[v][i];
                    const Cost pd = pot[v] - pot[e.to];
                    if (e.cap == 0 or dist[e.to] <= dist[v] + e.cost + pd) { continue; }
                    dist[e.to] = dist[v] + e.cost + pd, prev_v[e.to] = v, prev_e[e.to] = i;
                    q.push({dist[e.to], e.to});
                }
            }
            if (dist[t] == inf_v<Cost>) { return {false, ans}; }
            for (int v = 0; v < sz; v++) { pot[v] += dist[v]; }
            Cap d = f;
            for (int v = t; v != s; v = prev_v[v]) {
                const auto& e = edges[prev_v[v]][prev_e[v]];
                d             = std::min(d, e.cap);
            }
            f -= d, ans += static_cast<Result>(d) * static_cast<Result>(pot[t]);
            for (int v = t; v != s; v = prev_v[v]) {
                auto& e = edges[prev_v[v]][prev_e[v]];
                e.cap -= d, edges[v][e.rev].cap += d;
            }
        }
        return {true, ans};
    }
    friend std::ostream& operator<<(std::ostream& os, const cost_flow& cf)
    {
        os << "[\n";
        for (int i = 0; i < cf.size(); i++) {
            for (const auto& e : cf[i]) {
                if (not e.is_rev) { os << i << "->" << e.to << ":"
                                       << "<Cap=" << e.cap << ",Cost=" << e.cost << ">\n"; }
            }
        }
        return (os << "]\n");
    }
};
