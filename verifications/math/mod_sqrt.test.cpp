#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_mod"
#include "math/mod_sqrt.hpp"
#include "math/modint.hpp"
#include "misc/fastio/printer.hpp"
#include "misc/fastio/scanner.hpp"
#include "misc/random.hpp"
modinfo info;
using mint = modint<info>;
int main()
{
    const int T = in.val<int>();
    for (int t = 0; t < T; t++) {
        const auto [Y, P] = in.tup<uint, uint>();
        info.set_mod(P);
        const mint ans = modsqrt(mint{Y});
        if (ans * ans == Y) {
            out.ln(ans());
        } else {
            out.ln(-1);
        }
    }
    return 0;
}
