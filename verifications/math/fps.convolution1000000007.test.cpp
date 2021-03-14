#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"
#include "math/fps.hpp"
#include "misc/fastio/printer.hpp"
#include "misc/fastio/scanner.hpp"
int main()
{
    using mint        = modint_1000000007;
    const auto [N, M] = in.tup<int, int>();
    fps<mint> as(N), bs(M);
    for (auto& a : as) { a.set_raw(in.val<int>()); }
    for (auto& b : bs) { b.set_raw(in.val<int>()); }
    const auto cs = as * bs;
    std::vector<int> ans(cs.size());
    for (int i = 0; i < (int)cs.size(); i++) { ans[i] = cs[i](); }
    out.ln(ans);
    return 0;
}
