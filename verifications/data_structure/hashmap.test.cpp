#define PROBLEM "https://judge.yosupo.jp/problem/associative_array"
#include "data_structure/hashmap.hpp"
#include "misc/fastio/printer.hpp"
#include "misc/fastio/scanner.hpp"
int main()
{
    hashmap<u64, u64> dict;
    const auto Q = in.val<int>();
    for (int q = 0; q < Q; q++) {
        const auto t = in.val<int>();
        if (t == 0) {
            const auto [k, v] = in.tup<u64, u64>();
            dict[k]           = v;
        } else {
            const auto k = in.val<u64>();
            out.ln(dict[k]);
        }
    }
    return 0;
}
