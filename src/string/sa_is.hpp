#pragma once
#include <string>
#include <vector>
template<typename InIt>
std::vector<int> sa_is(const InIt first, const InIt last, int bucket_size = (1UL << 8))
{
    bucket_size++;
    const int sz = (int)std::distance(first, last);
    std::vector<bool> isL(sz + 1, false), isLMS(sz + 1, false);
    std::vector<int> spos(bucket_size, 0), lpos(bucket_size, 0), S(sz + 1, 0), nextLMS(sz + 1, sz + 1), LMS;
    std::vector<std::vector<int>> sBucket(bucket_size), lBucket(bucket_size);
    for (int i = 0; i < sz; i++) { S[i] = *std::next(first, i) + 1; }
    sBucket[0].push_back(sz + 1);
    for (int j = 1, pos = sz; j <= sz; j++) {
        int i      = sz - j;
        isL[i]     = S[i] > S[i + 1] or (S[i] == S[i + 1] and isL[i + 1]), (isL[i] ? lBucket[S[i]].push_back(sz + 1) : sBucket[S[i]].push_back(sz + 1));
        nextLMS[i] = pos;
        if (isL[i] and not isL[i + 1]) { LMS.push_back(i + 1), isLMS[i + 1] = true, sBucket[S[i + 1]][spos[S[i + 1]]++] = i + 1, pos = i + 1; }
    }
    auto induce = [&]() {
        auto insert = [&](const int i, const bool isl) {
            if (i == 0 or isl != isL[i - 1]) { return; }
            if (isL[i - 1]) {
                lBucket[S[i - 1]][lpos[S[i - 1]]++] = i - 1;
            } else {
                sBucket[S[i - 1]][spos[S[i - 1]]++] = i - 1;
            }
        };
        for (int k = 0; k < bucket_size; k++) {
            for (int i = 0; i < lpos[k]; i++) { insert(lBucket[k][i], true); }
            for (int i = 1; i <= spos[k]; i++) { insert(sBucket[k][spos[k] - i], true); }
        }
        std::fill(spos.begin() + 1, spos.end(), 0);
        for (int i = 1; i <= bucket_size; i++) {
            const int k = bucket_size - i;
            for (int i = 0; i < spos[k]; i++) { insert(sBucket[k][i], false); }
            for (int i = 1; i <= lpos[k]; i++) { insert(lBucket[k][lpos[k] - i], false); }
        }
    };
    induce();
    std::vector<int> lms;
    for (int k = 0; k < bucket_size; k++) {
        for (auto it = lBucket[k].begin(); it < lBucket[k].end(); it++) {
            if (isLMS[*it]) { lms.push_back(*it); }
        }
        for (auto it = sBucket[k].rbegin(); it < sBucket[k].rend(); it++) {
            if (isLMS[*it]) { lms.push_back(*it); }
        }
    }
    bool distinct = true;
    int number    = 1;
    std::vector<int> ord((sz + 1) / 2 + 1, 0);
    ord[(sz + 1) / 2] = 1;
    for (int i = 1; i < lms.size(); i++) {
        const int l1 = lms[i - 1], r1 = nextLMS[l1], l2 = lms[i], r2 = nextLMS[l2];
        if (r1 - l1 == r2 - l2 and std::vector<int>(S.begin() + l1, S.begin() + r1 + 1) == std::vector<int>(S.begin() + l2, S.begin() + r2 + 1)) {
            distinct = false;
        } else {
            number++;
        }
        ord[l2 / 2] = number;
    }
    std::vector<int> sub;
    for (const auto o : ord) {
        if (o > 0) { sub.push_back(o); }
    }
    if (not distinct) {
        const auto sorted = sa_is(sub.begin(), sub.end(), number + 1);
        for (int k = 0; k < bucket_size; k++) { spos[k] = lpos[k] = 0; }
        for (int j = 1; j <= lms.size(); j++) {
            const int i                     = lms.size() - j;
            const auto ind                  = LMS[lms.size() - 1 - sorted[i]];
            sBucket[S[ind]][spos[S[ind]]++] = ind;
        }
    } else {
        for (int k = 0; k < bucket_size; k++) { spos[k] = lpos[k] = 0; }
        for (auto it = lms.rbegin(); it < lms.rend(); it++) { sBucket[S[*it]][spos[S[*it]]++] = *it; }
    }
    induce();
    std::vector<int> ans;
    for (int k = 1; k < bucket_size; k++) {
        for (auto it = lBucket[k].begin(); it < lBucket[k].end(); it++) { ans.push_back(*it); }
        for (auto it = sBucket[k].rbegin(); it < sBucket[k].rend(); it++) { ans.push_back(*it); }
    }
    return ans;
}
