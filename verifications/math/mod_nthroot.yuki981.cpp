// clang-format off
#include "math/moddint.hpp"
#include "math/moddint64.hpp"
#include "math/mod_nthroot.hpp"
#include "misc/fastio/printer.hpp"
#include "misc/fastio/scanner.hpp"
// clang-format on
moddinfo info;
using mint = moddint<info>;
moddinfo64 info64;
using mint64 = moddint64<info64>;
int main()
{
    const int T = in.val<int>();
    for (int t = 0; t < T; t++) {
        const auto [P, K, A] = in.tup<u64, u64, u64>();
        if (P == 2) {
            out.ln(A == 1 ? 1 : K == 0 ? -1 : 0);
            continue;
        }
        if (P < (1ULL << 30)) {
            info.set_mod(P);
            const mint ans = mod_nthroot(mint(A), K);
            if (ans.pow(K) == A) {
                out.ln(ans());
            } else {
                out.ln(-1);
            }
        } else {
            info64.set_mod(P);
            const mint64 ans = mod_nthroot(mint64(A), K);
            if (ans.pow(K) == A) {
                out.ln(ans());
            } else {
                out.ln(-1);
            }
        }
    }
    return 0;
}
