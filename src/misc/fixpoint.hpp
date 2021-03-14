#pragma once
#include <utility>
template<typename F> struct fix : F
{
    fix(F&& f) : F{std::forward<F>(f)} {}
    template<typename... Args> auto operator()(Args&&... args) const { return F::operator()(*this, std::forward<Args>(args)...); }
};
