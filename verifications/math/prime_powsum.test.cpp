#define PROBLEM "https://judge.yosupo.jp/problem/counting_primes"
#include "math/prime_powsum.hpp"
#include "misc/fastio/printer.hpp"
#include "misc/fastio/scanner.hpp"
int main()
{
    const auto N = in.val<u64>();
    if (N <= 2) { return out.ln(N == 2 ? 1 : 0); }
    const auto powsum = prime_powsum<u64>(N);
    out.ln(powsum.get(0, N));
    return 0;
}
