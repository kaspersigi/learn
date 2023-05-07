#include <algorithm>
#include <array>
#include <iostream>
#include <set>
#include <string>

#if 0
bool is_anagram(std::string s, std::string t)
{
    if (s.length() != t.length())
        return false;
    std::multiset<char> ss {};
    std::multiset<char> st {};
    std::for_each(s.cbegin(), s.cend(), [&](auto e) { ss.insert(e); });
    std::for_each(t.cbegin(), t.cend(), [&](auto e) { st.insert(e); });
    return std::equal(ss.cbegin(), ss.cend(), st.cbegin());
}
#endif

#if 1
// 数组是最简单的哈希表，比法一，快得多
bool is_anagram(std::string s, std::string t)
{
    if (s.length() != t.length())
        return false;
    std::array<int, 26> as {};
    std::array<int, 26> at {};
    std::for_each(s.cbegin(), s.cend(), [&](auto e) { as[e - 'a']++; });
    std::for_each(t.cbegin(), t.cend(), [&](auto e) { at[e - 'a']++; });
    return std::equal(as.cbegin(), as.cend(), at.cbegin());
}
#endif

auto main(int argc, char* argv[]) -> int
{
    std::string s { "anagram" };
    std::string t { "nagaram" };
    std::cout << is_anagram(s, t) << std::endl;
    return 0;
}