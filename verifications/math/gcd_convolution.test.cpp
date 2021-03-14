#define PROBLEM "https://yukicoder.me/problems/no/886"
#include "math/gcd_convolution.hpp"
#include "math/modint.hpp"
#include "misc/fastio/printer.hpp"
#include "misc/fastio/scanner.hpp"
int main()
{
    using mint        = modint_1000000007;
    const auto [H, W] = in.tup<int, int>();
    mint ans          = mint(H) * (W - 1) + mint(H - 1) * W;
    std::vector<mint> as(H), bs(W);
    for (int i = 1; i < H; i++) { as[i] = H - i; }
    for (int i = 1; i < W; i++) { bs[i] = W - i; }
    const auto cs = gcd_convolute(as, bs);
    ans += (cs.size() < 2 ? mint{0} : cs[1]) * 2;
    out.ln(ans());
    return 0;
}
