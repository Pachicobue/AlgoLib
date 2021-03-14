#define PROBLEM "https://judge.yosupo.jp/problem/tree_diameter"
#include "graph/diameter.hpp"
#include "misc/fastio/printer.hpp"
#include "misc/fastio/scanner.hpp"
#include "misc/types.hpp"
int main()
{
    const auto N = in.val<int>();
    graph<ll> g(N);
    for (int i = 0; i < N - 1; i++) {
        const auto [u, v, c] = in.tup<int, int, ll>();
        g.add_edge(u, v, c, true);
    }
    auto [r, es] = diameter(g);
    ll X         = 0;
    std::vector<int> us{r};
    for (const int i : es) {
        [[maybe_unused]] const auto [from, to, cost] = g.edge(r, i);
        X += cost, r = to;
        us.push_back(r);
    }
    out.ln(X, us.size());
    out.ln(us);
    return 0;
}
