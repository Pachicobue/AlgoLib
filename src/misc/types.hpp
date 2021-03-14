#pragma once
#include <queue>
using i32  = int;
using u32  = unsigned int;
using i64  = long long;
using u64  = unsigned long long;
using i128 = __int128_t;
using u128 = __uint128_t;
using f64  = double;
using f80  = long double;
using f128 = __float128;

using uint                          = unsigned int;
using ll                            = long long;
using ull                           = unsigned long long;
using ld                            = long double;
using LL                            = __int128_t;
using ULL                           = __uint128_t;
template<typename T> using max_heap = std::priority_queue<T>;
template<typename T> using min_heap = std::priority_queue<T, std::vector<T>, std::greater<T>>;
