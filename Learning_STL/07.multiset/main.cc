#include <algorithm>
#include <iostream>
#include <set>

auto main(int argc, char* argv[]) -> int
{
    std::multiset nums {
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

    std::cout << nums.size() << std::endl;
    std::cout << nums.max_size() << std::endl;

    auto it = nums.find(4);

    auto count = nums.erase(4); // 全部删除
    std::cout << count << std::endl;

    std::for_each(nums.cbegin(), nums.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;

    auto pair = nums.insert(4);

    std::for_each(nums.cbegin(), nums.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;

    std::cout << nums.count(5) << std::endl;

    return 0;
}