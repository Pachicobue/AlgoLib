#pragma once
#ifndef WITHOUT_STANDARD_LIBRARY
#    include <iostream>
#    include <tuple>
#endif
template<typename TupType, size_t... I>
std::ostream& print(std::ostream& os, const TupType& _tup, std::index_sequence<I...>) { return os << "(", (..., (os << (I == 0 ? "" : ", ") << std::get<I>(_tup))), os << ")\n"; }
template<typename... T>
std::ostream& operator<<(std::ostream& os, const std::tuple<T...>& _tup) { return print(os, _tup, std::make_index_sequence<sizeof...(T)>()); }
