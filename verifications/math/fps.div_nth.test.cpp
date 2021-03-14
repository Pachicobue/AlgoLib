#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include "math/fps_div_nth.hpp"
#include "misc/fastio/printer.hpp"
#include "misc/fastio/scanner.hpp"
#include "misc/random.hpp"
int main()
{
    const auto [A, B] = in.tup<int, int>();
    using mint        = modint_1000000007;
    const auto K      = rng.val<int>(2, 10);
    const auto N      = rng.val<ll>(1, 1000000000);
    using vec         = std::vector<mint>;
    using mat         = std::vector<vec>;
    std::vector<mint> as(K);
    for (auto& a : as) { a = rng.val<int>(0, mint::mod - 1); }
    mat css(K, vec(K, 0));
    for (int i = 0; i < K - 1; i++) { css[i][i + 1] = 1; }
    for (int j = 0; j < K; j++) { css[K - 1][j] = 1; }
    auto mul = [&](const mat& m1, const mat& m2) {
        mat ans(K, vec(K, 0));
        for (int i = 0; i < K; i++) {
            for (int j = 0; j < K; j++) {
                for (int k = 0; k < K; k++) { ans[i][j] += m1[i][k] * m2[k][j]; }
            }
        }
        return ans;
    };
    auto pow = [&](auto self, const mat& m, const ll n) -> mat {
        if (n == 1) { return m; }
        if (n % 2 == 0) {
            return self(self, mul(m, m), n / 2);
        } else {
            return mul(m, self(self, m, n - 1));
        }
    };
    const auto Mat = pow(pow, css, N);
    mint actual    = 0;
    for (int j = 0; j < K; j++) { actual += Mat[0][j] * as[j]; }
    fps<mint> f(as);
    fps<mint> g(K + 1, -1);
    g[0]           = 1;
    f              = f.mult(g, K);
    const mint ans = div_nth(f, g, N);
    assert(actual == ans);
    out.ln(A + B);
    return 0;
}
