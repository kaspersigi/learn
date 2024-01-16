#include <algorithm>
#include <iostream>
#include <vector>

auto main(int argc, char* argv[]) -> int
{
    std::vector nums1 { 1, 3, 2, 2, 7, 5, 6, 1, 1, 2, 2 };
    std::vector nums2 { 1, 3, 2, 2, 7, 5, 6, 1, 1, 2, 2 };
    std::vector nums3 { 1, 1, 1, 2, 2, 2, 2, 3, 5, 6, 7 };

    auto result1 = std::equal(nums1.cbegin(), nums1.cend(), nums2.cbegin());
    std::cout << result1 << std::endl;

    auto result2 = std::is_permutation(nums1.cbegin(), nums1.cend(), nums3.cbegin());
    std::cout << result2 << std::endl;

    return 0;
}