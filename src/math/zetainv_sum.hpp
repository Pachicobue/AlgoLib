#pragma once
#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>
#include "../misc/types.hpp"
template<typename T, typename V>
class zetainv_sum
{
public:
    template<typename F, typename SumAccum>
    zetainv_sum(const T N, F f, SumAccum sum_accum, int M = 0) : N{N}, SQRT{sqrt(N)}, MEMO{memo(N, M)}
    {
        init();
        init_smalls(f), init_larges();
        for (int i = 1; i < nn; i++) {
            const int num = ns[i];
            if (num <= MEMO) { continue; }
            int n = 0;
            for (; n * n < N; n++) {}
            V sum = sum_accum(N);
            for (int j = 2; j <= n; j++) { sum -= Vs[rev(N / (T)j)]; }
            for (int k = 1; k <= n; k++) {
                const int j = rev(k);
                const int L = std::max(N / (k + 1), n), R = N / k;
                if (L < R) { sum -= (V)(R - L) * Vs[j]; }
            }
            Vs[i] = sum;
        }
    }
    V operator()(const T n) const
    {
        const int i = rev(n);
        assert(ns[i] == n);
        return Vs[i];
    }

private:
    static int sqrt(const T n)
    {
        int ans = (int)std::sqrt(n);
        for (; (T)(ans + 1) * (T)(ans + 1) <= n; ans++) {}
        return ans;
    }
    static int memo(const T n, const int m)
    {
        if (m != 0) { return m; }
        int ans = (int)std::pow(n, double(2) / 3);
        for (; (T)ans * (T)ans * (T)ans < n * n; ans++) {}
        return ans;
    }
    void init()
    {
        for (T p = 1; p * p <= N; p++) { ns.push_back(p), ns.push_back(N / p); }
        std::sort(ns.begin(), ns.end());
        ns.erase(std::unique(ns.begin(), ns.end()), ns.end());
        nn = ns.size();
    }
    template<typename F>
    void init_smalls(const F& f)
    {
        V_smalls.resize(MEMO + 1);
        for (int i = 0; i <= MEMO; i++) { V_smalls[i] = f(i); }
        for (int i = 1; i <= MEMO; i++) { V_smalls[i] += V_smalls[i - 1]; }
    }
    void init_larges()
    {
        Vs.resize(nn, 0);
        Vs[0] = V_smalls[1];
        for (int i = 1; i < nn; i++) {
            if (ns[i] > MEMO) { break; }
            Vs[i] = V_smalls[ns[i]];
        }
    }
    int rev(const T n) const { return n <= SQRT ? (int)(n - 1) : nn - (int)(N / n); }
    T N = 0;
    const int SQRT, MEMO;
    int nn;
    std::vector<T> ns;  // \lfloor \frac{N}{i} \rfloor
    std::vector<V> Vs;
    std::vector<V> V_smalls;
};
