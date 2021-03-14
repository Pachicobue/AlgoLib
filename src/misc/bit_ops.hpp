#pragma once
#include "types.hpp"
constexpr int popcount(const ull v) { return v ? __builtin_popcountll(v) : 0; }
constexpr int log2p1(const ull v) { return v ? 64 - __builtin_clzll(v) : 0; }
constexpr int lsbp1(const ull v) { return __builtin_ffsll(v); }
constexpr int clog(const ull v) { return v ? log2p1(v - 1) : 0; }
constexpr ull ceil2(const ull v) { return 1ULL << clog(v); }
constexpr ull floor2(const ull v) { return v ? (1ULL << (log2p1(v) - 1)) : 0ULL; }
constexpr bool ispow2(const ull v) { return (v & (v - 1)) == 0; }
constexpr bool btest(const ull mask, const int ind) { return (mask >> ind) & 1ULL; }
