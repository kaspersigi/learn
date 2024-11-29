#include <algorithm>
#include <iostream>
#include <unordered_set>

auto main(int argc, char* argv[]) -> int
{
    std::unordered_multiset nums {
        1,
        2,
        2,
        3,
        3,
        3,
        4,
        4,
        4,
        4,
        5,
        5,
        5,
        5,
        5,
    };

    std::for_each(nums.cbegin(), nums.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;

    decltype(nums) nums2;
    nums2.insert(3);
    nums2.insert(3);
    nums2.insert(3);
    nums2.insert(2);
    nums2.insert(2);
    nums2.insert(1);
    std::for_each(nums2.cbegin(), nums2.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;

    std::cout << nums.size() << std::endl;
    std::cout << nums.max_size() << std::endl;

    auto count = nums.erase(3);
    std::cout << count << std::endl;

    std::for_each(nums.cbegin(), nums.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;

    auto pair = nums.insert(3);

    std::for_each(nums.cbegin(), nums.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;

    return 0;
}