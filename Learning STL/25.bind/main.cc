#include <functional>
#include <iostream>

auto main(int argc, char* argv[]) -> int
{
    auto f = std::bind(std::multiplies<int>(), std::placeholders::_1, 10);
    std::cout << f(3) << std::endl;

    auto plus10 = std::bind(std::plus<int>(), std::placeholders::_1, 10);
    std::cout << plus10(7) << std::endl;

    // auto plus10times2 = std::bind(std::multiplies<int>(), plus10, 2);
    auto plus10times2 = std::bind(std::multiplies<int>(), std::bind(std::plus<int>(), std::placeholders::_1, 10), 2);
    std::cout << plus10times2(7) << std::endl;

    auto pow3 = std::bind(std::multiplies<int>(), std::bind(std::multiplies<int>(), std::placeholders::_1, std::placeholders::_1), std::placeholders::_1);
    std::cout << pow3(5) << std::endl;

    return 0;
}