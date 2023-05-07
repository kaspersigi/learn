#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

#if 0
std::vector<int> intersection(std::vector<int>& nums1, std::vector<int>& nums2)
{
    std::vector<int> answer {};
    std::array<int, 1001> ai1 {};
    std::array<int, 1001> ai2 {};
    std::for_each(nums1.cbegin(), nums1.cend(), [&](auto e) { ai1[e]++; });
    std::for_each(nums2.cbegin(), nums2.cend(), [&](auto e) { ai2[e]++; });
    for (int i = 0; i < 1001; ++i) {
        if (ai1[i] && ai2[i])
            answer.push_back(i);
    }
    return answer;
}
#endif

std::vector<int> intersection(std::vector<int>& nums1, std::vector<int>& nums2)
{
    std::vector<int> answer {};
    std::array<int, 1001> ai {};
    std::for_each(nums1.cbegin(), nums1.cend(), [&](auto e) { ai[e]++; });
    std::for_each(nums2.cbegin(), nums2.cend(), [&](auto e) { if(ai[e]) {answer.push_back(e);ai[e]=0;} });
    return answer;
}

auto main(int argc, char* argv[]) -> int
{
    std::vector<int> vi1 { 1, 2, 2, 1 };
    std::vector<int> vi2 { 2, 2 };
    auto answer = intersection(vi1, vi2);
    std::for_each(answer.cbegin(), answer.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;
    return 0;
}