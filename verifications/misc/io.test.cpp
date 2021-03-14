#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"
#include "misc/printer.hpp"
#include "misc/scanner.hpp"
int main()
{
    using ll     = long long;
    const auto T = in.val<int>();
    for (int t = 0; t < T; t++) {
        const auto [A, B] = in.tup<ll, ll>();
        out.ln(A + B);
    }
    return 0;
}
