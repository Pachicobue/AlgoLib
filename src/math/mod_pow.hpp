#pragma once
template<typename T>
T mod_pow(T x, T n, const T mod)
{
    T ans = T{1} % mod;
    for (; n; n >>= 1, (x *= x) %= mod) {
        if (n & 1) { (ans *= x) %= mod; }
    }
    return ans;
}
