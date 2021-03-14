#pragma once
#include <cmath>
#include <iostream>
template<typename T>
struct complex
{
    constexpr complex() : real{T{0}}, imag{T{0}} {}
    constexpr complex(const T r, const T i) : real{r}, imag{i} {}
    constexpr complex polar(const T r, const T s) { real = r * std::cos(s), imag = r * std::sin(s); }
    constexpr complex conj() const { return complex{real, -imag}; }
    constexpr T norm() const { return real * real + imag * imag; }
    constexpr T abs() const { return std::sqrt(norm()); }
    constexpr T arg() const { return std::atan2(imag, real); }
    complex operator-() { return complex{-real, -imag}; }
    complex operator+(const complex& c) const { return complex{*this} += c; }
    complex operator-(const complex& c) const { return complex{*this} -= c; }
    complex operator*(const complex& c) const { return complex{real * c.real - imag * c.imag, real * c.imag + imag * c.real}; }
    complex operator/(const complex& c) const { return (*this) * c.conj() / c.norm(); }
    complex operator+(const T v) const { return complex{*this} += v; }
    complex operator-(const T v) const { return complex{*this} -= v; }
    complex operator*(const T v) const { return complex{*this} *= v; }
    complex operator/(const T v) const { return complex{*this} /= v; }
    friend complex operator+(const T v, const complex& c) { return complex{v + c.real, c.imag}; }
    friend complex operator-(const T v, const complex& c) { return complex{v - c.real, -c.imag}; }
    friend complex operator*(const T v, const complex& c) { return complex{v * c.real, v * c.imag}; }
    friend complex operator/(const T v, const complex& c) { return v * c.conj() / c.norm(); }
    complex& operator+=(const complex& c) { return real += c.real, imag += c.imag, *this; }
    complex& operator-=(const complex& c) { return real -= c.real, imag -= c.imag, *this; }
    complex& operator*=(const complex& c) { return (*this) = (*this) * c; }
    complex& operator/=(const complex& c) { return (*this) = (*this) / c; }
    complex& operator+=(const T v) { return real += v, *this; }
    complex& operator-=(const T v) { return real -= v, *this; }
    complex& operator*=(const T v) { return real *= v, imag *= v, *this; }
    complex& operator/=(const T v) { return real /= v, imag /= v, *this; }
    bool operator==(const complex& c) const { return real == c.real and imag == c.imag; }
    bool operator!=(const complex& c) const { return not(*this == c); }
    friend std::ostream& operator<<(std::ostream& os, const complex& c) { return os << c.real << "+" << c.imag << "I"; }
    T real, imag;
};
