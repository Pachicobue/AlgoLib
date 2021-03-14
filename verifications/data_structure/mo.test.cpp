#define PROBLEM "https://judge.yosupo.jp/problem/static_range_inversions_query"
#include "data_structure/fenwick.hpp"
#include "data_structure/hashmap.hpp"
#include "data_structure/mo.hpp"
#include "misc/fastio/printer.hpp"
#include "misc/fastio/scanner.hpp"
int main()
{
    const auto [N, Q] = in.tup<int, int>();
    auto as           = in.vec<u32>(N);
    auto unzip        = as;
    std::sort(unzip.begin(), unzip.end());
    unzip.erase(std::unique(unzip.begin(), unzip.end()), unzip.end());
    hashmap<u32, int> zip;
    const int L = (int)unzip.size();
    for (int i = 0; i < L; i++) { zip[unzip[i]] = i; }
    for (auto& a : as) { a = zip[a]; }

    fenwick<int> bit(std::vector<int>(L, 0));
    u64 inv   = 0;
    auto left = [&](const int x, const int) {  // (x,y)->(x-1,y)
        const int a = as[x - 1];
        inv += bit.sum(0, a);
        bit.add(a, 1);
    };
    auto right = [&](const int x, const int) {  // (x,y)->(x+1,y)
        const int a = as[x];
        inv -= bit.sum(0, a);
        bit.add(a, -1);
    };
    auto up = [&](const int, const int y) {  // (x,y)->(x,y-1)
        const int a = as[y - 1];
        inv -= bit.sum(a + 1, L);
        bit.add(a, -1);
    };
    auto down = [&](const int, const int y) {  // (x,y)->(x,y+1)
        const int a = as[y];
        inv += bit.sum(a + 1, L);
        bit.add(a, 1);
    };

    std::vector<int> ls(Q), rs(Q);
    for (int q = 0; q < Q; q++) { std::tie(ls[q], rs[q]) = in.tup<int, int>(); }
    mo_iterator<300> mo(ls, rs);
    std::vector<u64> ans(Q);
    for (int q = 0; q < Q; q++) {
        const int it = mo.next(right, left, down, up);
        ans[it]      = inv;
    }
    out.ln(ans);

    return 0;
}
