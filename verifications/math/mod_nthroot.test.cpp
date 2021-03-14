#define PROBLEM "https://judge.yosupo.jp/problem/kth_root_mod"
#include "math/mod_nthroot.hpp"
#include "math/moddint.hpp"
#include "misc/fastio/printer.hpp"
#include "misc/fastio/scanner.hpp"
moddinfo info;
using mint = moddint<info>;
int main()
{
    const int T = in.val<int>();
    for (int t = 0; t < T; t++) {
        const auto [K, Y, P] = in.tup<uint, uint, uint>();
        if (P == 2) {
            out.ln(Y == 1 ? 1 : K == 0 ? -1 : 0);
            continue;
        }
        info.set_mod(P);
        const mint ans = mod_nthroot(mint{Y}, K);
        if (ans.pow(K) == Y) {
            out.ln(ans());
        } else {
            out.ln(-1);
        }
    }
    return 0;
}
