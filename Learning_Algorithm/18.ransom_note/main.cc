#include <algorithm>
#include <array>
#include <iostream>
#include <string>

#if 0
bool can_construct(std::string ransomNote, std::string magazine)
{
    if (magazine.length() < ransomNote.length())
        return false;
    std::array<size_t, 16> ac1 {};
    std::array<size_t, 16> ac2 {};
    std::for_each(ransomNote.cbegin(), ransomNote.cend(), [&](auto e) { ac1[e - 'a']++; });
    std::for_each(magazine.cbegin(), magazine.cend(), [&](auto e) { ac2[e - 'a']++; });
    for (size_t i = 0; i < 26; ++i) {
        if (ac2[i] < ac1[i])
            return false;
    }
    return true;
}
#endif

bool can_construct(std::string ransomNote, std::string magazine)
{
    if (magazine.length() < ransomNote.length())
        return false;
    std::array<int, 26> ac {};
    std::for_each(magazine.cbegin(), magazine.cend(), [&](auto e) { ac[e - 'a']++; });
    for (auto const& e : ransomNote) {
        if (--ac[e - 'a'] < 0)
            return false;
    }
    return true;
}

auto main(int argc, char* argv[]) -> int
{
    std::string ransomNote { "aa" };
    std::string magazine { "ab" };
    std::cout << can_construct(ransomNote, magazine) << std::endl;
    return 0;
}