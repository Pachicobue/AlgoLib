#define PROBLEM "https://judge.yosupo.jp/problem/factorize"
#include "math/prime_factors.hpp"
#include "misc/fastio/printer.hpp"
#include "misc/fastio/scanner.hpp"
int main()
{
    const auto Q = in.val<int>();
    for (int q = 0; q < Q; q++) {
        const auto a  = in.val<u64>();
        const auto fs = prime_factors(a);
        std::vector<u64> ans;
        for (const auto& [p, e] : fs) {
            for (int i = 0; i < e; i++) { ans.push_back(p); }
        }
        out.ln(ans.size(), ans);
    }
    return 0;
}
