#pragma once
#ifdef HOGEPACHI
#    include <iostream>
#    include "print/array.hpp"
#    include "print/deque.hpp"
#    include "print/int128_t.hpp"
#    include "print/map.hpp"
#    include "print/multimap.hpp"
#    include "print/multiset.hpp"
#    include "print/pair.hpp"
#    include "print/priority_queue.hpp"
#    include "print/queue.hpp"
#    include "print/set.hpp"
#    include "print/stack.hpp"
#    include "print/tuple.hpp"
#    include "print/unordered_map.hpp"
#    include "print/unordered_multimap.hpp"
#    include "print/unordered_multiset.hpp"
#    include "print/unordered_set.hpp"
#    include "print/vector.hpp"
#    define SHOW(...) (std::cerr << "LINE " << __LINE__ << ": "          \
                                 << "(" << #    __VA_ARGS__ << ") = ("), \
                      HogeHogeSansuu(__VA_ARGS__), std::cerr << ")" << std::endl
template<typename T>
void HogeHogeSansuu(T x) { std::cerr << x; }
template<typename T, typename... Args>
void HogeHogeSansuu(T x, Args... args) { std::cerr << x << ",", HogeHogeSansuu(args...); }
#else
#    define SHOW(...) static_cast<void>(0)
#endif
