#pragma once
#ifndef WITHOUT_STANDARD_LIBRARY
#    include <algorithm>
#    include <chrono>
#endif
class stopwatch
{
public:
    stopwatch() : start{std::chrono::system_clock::now()}, rap_point{start} {}
    template<typename Duration = std::chrono::milliseconds> long long rap()
    {
        const auto now = std::chrono::system_clock::now();
        return std::chrono::duration_cast<Duration>(now - std::exchange(rap_point, now)).count();
    }
    template<typename Duration = std::chrono::milliseconds> long long total() { return std::chrono::duration_cast<Duration>(std::chrono::system_clock::now() - start).count(); }

private:
    std::chrono::system_clock::time_point start, rap_point;
};
