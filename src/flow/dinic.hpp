#pragma once
#include <limits>
#include <queue>
#include "../misc/bit_ops.hpp"
#include "../misc/constants.hpp"
#include "flow.hpp"
template<typename T>
T dinic(flow<T>& flow, const int s, const int t, const T max_cap = inf_v<T>)
{
    const int sz = flow.size();
    std::vector<int> level(sz, sz), iter(sz, 0);
    auto bfs = [&, sz](const T base) {
        std::fill(level.begin(), level.end(), sz);
        std::queue<int> q;
        q.push(s), level[s] = 0;
        while (not q.empty()) {
            const int s = q.front();
            q.pop();
            for (const auto& e : flow[s]) {
                if (e.cap < base or level[e.to] != sz) { continue; }
                level[e.to] = level[s] + 1, q.push(e.to);
            }
        }
    };
    auto dfs = [&, sz](auto&& self, const int s, const T base, const T f) -> T {
        if (s == t) { return f; }
        T ans = 0;
        for (int& i = iter[s]; i < flow[s].size(); i++) {
            auto& e = flow[s][i];
            if (e.cap < base or level[e.to] == sz or level[s] >= level[e.to]) { continue; }
            const T d = self(self, e.to, base, std::min(f - ans, e.cap));
            if (d == 0) { continue; }
            e.cap -= d, flow[e.to][e.rev].cap += d, ans += d;
            if (f - ans < base) { break; }
        }
        return ans;
    };
    T f = 0;
    for (T base = floor2(max_cap); base >= 1;) {
        bfs(base);
        if (level[t] == sz) {
            base >>= 1;
            continue;
        }
        std::fill(iter.begin(), iter.end(), 0);
        const T df = dfs(dfs, s, base, inf_v<T>);
        f += df;
    }
    return f;
}
