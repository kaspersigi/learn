#include <algorithm>
#include <array>
#include <iostream>

auto main(int argc, char* argv[]) -> int
{
    std::array<int, 10> num1;
    std::fill_n(num1.begin(), num1.size(), 0);
    std::array<int, 10> num2 {
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
    std::for_each(num1.cbegin(), num1.cend(), [](auto e) { std::cout << e << ' ' << std::flush; });
    std::cout << std::endl;
    std::for_each(num2.cbegin(), num2.cend(), [](auto e) { std::cout << e << ' ' << std::flush; });
    std::cout << std::endl;

    std::copy(num2.cbegin(), num2.cend(), num1.begin());
    std::for_each(num1.cbegin(), num1.cend(), [](auto e) { std::cout << e << ' ' << std::flush; });
    std::cout << std::endl;

    return 0;
}