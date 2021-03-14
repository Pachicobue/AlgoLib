#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"
#include "math/fps.hpp"
#include "misc/fastio/printer.hpp"
#include "misc/fastio/scanner.hpp"
int main()
{
    using mint        = modint_998244353;
    const auto [N, M] = in.tup<int, int>();
    fps<mint> as(N), bs(M);
    for (int i = 0; i < N; i++) { as[i].set_raw(in.val<int>()); }
    for (int j = 0; j < M; j++) { bs[j].set_raw(in.val<int>()); }
    auto cs = as * bs;
    std::vector<int> ans(cs.size());
    for (int i = 0; i < (int)cs.size(); i++) { ans[i] = cs[i](); }
    out.ln(ans);
    return 0;
}
