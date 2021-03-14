#define PROBLEM "https://judge.yosupo.jp/problem/queue_operate_all_composite"
#include "data_structure/swag.hpp"
#include "math/modint.hpp"
#include "misc/fastio/printer.hpp"
#include "misc/fastio/scanner.hpp"
int main()
{
    using mint   = modint_998244353;
    using Func   = std::pair<mint, mint>;
    const auto Q = in.val<int>();
    struct SemiGroup
    {
        using T = Func;
        T operator()(const T& f2, const T& f1) const { return T{f1.first * f2.first, f1.first * f2.second + f1.second}; }
    };

    auto deque = swag<SemiGroup>{};
    for (int q = 0; q < Q; q++) {
        const auto t = in.val<int>();
        if (t == 0) {
            const auto [a, b] = in.tup<mint, mint>();
            deque.push_back(Func{a, b});
        } else if (t == 1) {
            deque.pop_front();
        } else {
            const auto x = in.val<mint>();
            if (deque.empty()) {
                out.ln(x());
            } else {
                const auto [a, b] = deque.fold();
                out.ln((a * x + b)());
            }
        }
    }
    return 0;
}
