#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_taylor_shift"
#include "math/fps.hpp"
#include "misc/fastio/printer.hpp"
#include "misc/fastio/scanner.hpp"
int main()
{
    using mint        = modint_998244353;
    const auto [N, c] = in.tup<int, int>();
    fps<mint> as(N);
    for (auto& a : as) { a.set_raw(in.val<int>()); }
    const auto bs = as.tshift(mint{c});
    std::vector<int> ans(N);
    for (int i = 0; i < N; i++) { ans[i] = bs.at(i)(); }
    out.ln(ans);
    return 0;
}
