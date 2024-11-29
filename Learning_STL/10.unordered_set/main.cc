#include <algorithm>
#include <iostream>
#include <unordered_set>

auto main(int argc, char* argv[]) -> int
{
    std::unordered_set nums {
        1,
        2,
        3,
        4,
        5,
        6,
        7,
        8,
    };

    std::for_each(nums.cbegin(), nums.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;

    decltype(nums) nums2;
    nums2.insert(8);
    nums2.insert(7);
    nums2.insert(6);
    nums2.insert(5);
    nums2.insert(4);
    nums2.insert(3);
    nums2.insert(2);
    nums2.insert(1);
    std::for_each(nums2.cbegin(), nums2.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;

    std::cout << nums.size() << std::endl;
    std::cout << nums.max_size() << std::endl;

    auto count = nums.erase(5);
    std::cout << count << std::endl;

    std::for_each(nums.cbegin(), nums.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;

    auto pair = nums.insert(5);
    std::cout << pair.second << std::endl;
    std::cout << *pair.first << std::endl;

    std::for_each(nums.cbegin(), nums.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;

    return 0;
}