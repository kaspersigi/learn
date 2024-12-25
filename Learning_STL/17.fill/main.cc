#include <algorithm>
#include <array>
#include <iostream>

auto main(int argc, char* argv[]) -> int
{
    std::array<int, 10> nums {
        1,
        2,
        3,
        4,
        5,
        6,
        7,
        8,
        9,
        10,
    };
    std::for_each(nums.cbegin(), nums.cend(), [](auto e) { std::cout << e << ' ' << std::flush; });
    std::cout << std::endl;

    std::fill(nums.begin(), nums.end(), 0);
    std::for_each(nums.cbegin(), nums.cend(), [](auto e) { std::cout << e << ' ' << std::flush; });
    std::cout << std::endl;

    return 0;
}