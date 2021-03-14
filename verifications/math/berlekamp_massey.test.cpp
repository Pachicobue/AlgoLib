#define PROBLEM "https://judge.yosupo.jp/problem/find_linear_recurrence"
#include "math/berlekamp_massey.hpp"
#include "math/modint.hpp"
#include "misc/fastio/printer.hpp"
#include "misc/fastio/scanner.hpp"
int main()
{
    using mint   = modint_998244353;
    const auto N = in.val<int>();
    std::vector<mint> as(N);
    for (auto& a : as) { a = in.val<int>(); }
    const auto cs = berlekamp_massey(as);
    const int d   = cs.size();
    std::vector<int> ans(d - 1);
    for (int i = 1; i < d; i++) { ans[i - 1] = (-cs[i])(); }
    out.ln(d - 1);
    out.ln(ans);
    return 0;
}
