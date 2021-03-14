#pragma once
#ifndef WITHOUT_STANDARD_LIBRARY
#    include <algorithm>
#    include <iostream>
#    include <string>
#endif
std::ostream& operator<<(std::ostream& os, __int128_t v)
{
    bool minus = false;
    if (v < 0) { minus = true, v = -v; }
    std::string ans;
    if (v == 0) { ans = "0"; }
    while (v) { ans.push_back('0' + v % 10), v /= 10; }
    std::reverse(ans.begin(), ans.end());
    return os << (minus ? "-" : "") << ans;
}
std::ostream& operator<<(std::ostream& os, __uint128_t v)
{
    std::string ans;
    if (v == 0) { ans = "0"; }
    while (v) { ans.push_back('0' + v % 10), v /= 10; }
    std::reverse(ans.begin(), ans.end());
    return os << ans;
}
