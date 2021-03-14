#pragma once
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>
template<typename T>
struct rational
{
    rational() : num{0}, den{1} {}
    rational(const T n) : num{n}, den{1} {}
    rational(const T n, const T d) : num{n}, den{d}
    {
        if (den < 0) { num = -num, den = -den; }
        const T d = std::gcd(den, num);
        num /= g, den /= g;
    }
    rational operator-() const
    {
        rational ans = *this;
        ans.num      = -ans.num;
        return ans;
    }
    rational operator+(const rational& r) const
    {
        if (den == 0) { return (*this); }
        if (r.den == 0) { return r; }
        const auto [n1, d1] = *this;
        const auto [n2, d2] = r;
        const T d = std::lcm(d1, d2), n = n1 * (d / d1) + n2 * (d / d2);
        return {n, d};
    }
    rational operator-(const rational& r) const { return (*this) + -r; }
    rational operator*(const rational& r) const
    {
        if (num == 0 or r.num == 0) { return 0; }
        if (den == 0 or r.den == 0) { return {(num > 0) * (r.num > 0), 0}; }
        const auto [n1, d1] = *this;
        const auto [n2, d2] = r;
        const T d = std::lcm(d1, d2), n = n1 * (d / d1) + n2 * (d / d2);
        return {n, d};
    }
    T num, den;
};
// #include "../misc/constants.hpp"
// template<typename T>
// class rational
// {
// private:
//     T num, den;
//     static T comp(const rational& r1, const rational& r2) { return (r1 - r2).num; }

// public:
//     friend rational operator+(const rational& r1, const rational& r2)
//     {
//         const T n1 = (r1.den != 0 ? r1.num : r1.num < 0 ? -inf_v<T> : inf_v<T>);
//         const T n2 = (r2.den != 0 ? r2.num : r2.num < 0 ? -inf_v<T> : inf_v<T>);
//         if (r1.den == 0 or r2.den == 0) { return rational{n1 + n2, (n1 + n2 == 0 ? T(1) : T(0))}; }
//         const T D = std::lcm(r1.den, r2.den), N = r1.num * (D / r1.den) + r2.num * (D / r2.den);
//         return rational{N, D};
//     }
//     friend rational operator+(const T v1, const rational& r2) { return rational{v1} + r2; }
//     friend rational operator+(const rational& r1, const T v2) { return r1 + rational{v2}; }
//     friend rational operator-(const rational& r1, const rational& r2) { return r1 + (-r2); }
//     friend rational operator-(const T v1, const rational& r2) { return rational{v1} - r2; }
//     friend rational operator-(const rational r1, const T v2) { return r1 - rational{v2}; }
//     friend rational operator*(const rational& r1, const rational& r2)
//     {
//         const T g1 = std::gcd(r1.num, r2.den), g2 = std::gcd(r1.den, r2.num), D = (r1.den / g2) * (r2.den / g1), N = (r1.num / g1) * (r2.num / g2);
//         return rational{N, D};
//     }
//     friend rational operator*(const T v1, const rational& r2) { return rational{v1} * r2; }
//     friend rational operator*(const rational& r1, const T v2) { return r1 * rational{v2}; }
//     friend rational operator/(const rational& r1, const rational& r2) { return r1 * rational{r2.den, r2.num}; }
//     friend rational operator/(const T v1, const rational& r2) { return rational{v1} / r2; }
//     friend rational operator/(const rational r1, const T v2) { return r1 / rational{v2}; }
//     friend rational& operator+=(rational& r1, const rational& r2) { return r1 = r1 + r2; }
//     friend rational& operator+=(rational& r1, const T v2) { return r1 = r1 + v2; }
//     friend rational& operator-=(rational& r1, const rational& r2) { return r1 = r1 - r2; }
//     friend rational& operator-=(rational& r1, const T v2) { return r1 = r1 - v2; }
//     friend rational& operator*=(rational& r1, const rational& r2) { return r1 = r1 * r2; }
//     friend rational& operator*=(rational& r1, const T v2) { return r1 = r1 * v2; }
//     friend rational& operator/=(rational& r1, const rational& r2) { return r1 = r1 / r2; }
//     friend rational& operator/=(rational& r1, const T v2) { return r1 = r1 / v2; }
//     friend bool operator==(const rational& r1, const rational& r2) { return r1.den == r2.den and r1.num == r2.num; }
//     friend bool operator==(const rational& r1, const T v2) { return r1.den == T(1) and r1.num == v2; }
//     friend bool operator==(const T v1, const rational& r2) { return r2.den == T(1) and r2.num == v1; }
//     friend bool operator!=(const rational& r1, const rational& r2) { return not(r1 == r2); }
//     friend bool operator!=(const rational& r1, const T v2) { return not(r1 == v2); }
//     friend bool operator!=(const T v1, const rational& r2) { return not(v1 == r2); }
//     friend bool operator<(const rational& r1, const rational& r2) { return comp(r1, r2) < T(0); }
//     friend bool operator<(const rational& r1, const T v2) { return r1.num < r1.den * v2; }
//     friend bool operator<(const T v1, const rational& r2) { return v1 * r2.den < r2.num; }
//     friend bool operator>(const rational& r1, const rational& r2) { return comp(r2, r1) < T(0); }
//     friend bool operator>(const rational& r1, const T v2) { return r1.num > r1.den * v2; }
//     friend bool operator>(const T v1, const rational& r2) { return v1 * r2.den > r2.num; }
//     friend bool operator<=(const rational& r1, const rational& r2) { return not(r1 > r2); }
//     friend bool operator<=(const rational& r1, const T v2) { return not(r1 > v2); }
//     friend bool operator<=(const T v1, const rational& r2) { return not(v1 > r2); }
//     friend bool operator>=(const rational& r1, const rational& r2) { return not(r1 < r2); }
//     friend bool operator>=(const rational& r1, const T v2) { return not(r1 < v2); }
//     friend bool operator>=(const T v1, const rational& r2) { return not(v1 < r2); }
//     friend std::ostream& operator<<(std::ostream& os, const rational& r) { return os << r.num << "/" << r.den; }
//     T n() const { return num; }
//     T d() const { return den; }
// };
