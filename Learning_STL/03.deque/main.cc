#include <algorithm>
#include <deque>
#include <iostream>

auto main(int argc, char* argv[]) -> int
{
    std::deque nums {
        1,
        0,
        2,
        3,
        0,
        4,
        5,
        6,
        0,
        7,
        8,
        9,
    };
    std::cout << nums.size() << std::endl;
    std::cout << nums.max_size() << std::endl;

    nums.erase(std::remove(nums.begin(), nums.end(), 0), nums.end());
    std::for_each(nums.cbegin(), nums.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;
    std::cout << nums.size() << std::endl;
    std::cout << nums.max_size() << std::endl;

    nums.shrink_to_fit(); // deque内存模型和vector不一样，不需要capacity

    // 其他几乎同vector

    return 0;
}