#pragma once
#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>
template<typename T>
class prime_count
{
public:
    prime_count(const T N) : N{N}, SQRT{sqrt(N)}, isp(SQRT + 1, true)
    {
        assert(N >= 2);
        init();
        init_smalls();
        init_larges();
        for (int i = 0; i < pn; i++) {
            const int p = ps[i];
            for (int j = nn; (j--) > 0;) {
                const T n = ns[j];
                if (n < (T)p * (T)p) { break; }
                const T pn   = n / (T)p;
                const int pj = rev(pn);
                assert(C_smalls[p - 1] == i);
                Cs[j] -= Cs[pj] - C_smalls[p - 1];
            }
        }
    }
    T count(const T n) const
    {
        const int i = rev(n);
        assert(ns[i] == n);
        return Cs[i];
    }

private:
    static int sqrt(const T n)
    {
        int ans = std::sqrt(n);
        for (; (T)(ans + 1) * (T)(ans + 1) <= n; ans++) {}
        return ans;
    }
    void init()
    {
        isp[0] = false, isp[1] = false;
        for (int p = 2; p <= SQRT; p++) {
            if (not isp[p]) { continue; }
            ps.push_back(p);
            for (int q = p * 2; q <= SQRT; q += p) { isp[q] = false; }
        }
        for (T p = 1; p * p <= N; p++) { ns.push_back(p), ns.push_back(N / p); }
        std::sort(ns.begin(), ns.end());
        ns.erase(std::unique(ns.begin(), ns.end()), ns.end());
        pn = ps.size(), nn = ns.size();
    }
    void init_smalls()
    {
        C_smalls.resize(SQRT + 1, 0);
        for (int n = 1; n <= SQRT; n++) {
            if (not isp[n]) { continue; }
            C_smalls[n] = isp[n] ? (T)1 : (T)0;
        }
        for (int n = 1; n <= SQRT; n++) { C_smalls[n] += C_smalls[n - 1]; }
    }
    void init_larges()
    {
        Cs.resize(nn, 0);
        for (int i = 0; i < nn; i++) { Cs[i] = (T)ns[i] - (T)1; }
    }
    int rev(const T n) const { return n <= SQRT ? (int)(n - 1) : nn - (int)(N / n); }
    T N = 0;
    const int SQRT;
    int pn, nn;
    std::vector<bool> isp;
    std::vector<int> ps;
    std::vector<T> ns;
    std::vector<T> Cs;
    std::vector<T> C_smalls;
};
