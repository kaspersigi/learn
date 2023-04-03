// HJ6 质数因子
#include <algorithm>
#include <iostream>
#include <vector>

// 太慢了，需要优化
#if 0
auto main(int argc, char* argv[]) -> int {
    unsigned long number {};
    while (std::cin >> number) {
        std::vector<unsigned long> answer {};
        if (number <= 2)
            answer.push_back(number);
        else {
            unsigned long floor = number;
            for (size_t i = 2; i <= floor; ++i) {
                while (0 == floor % i) {
                    answer.push_back(i);
                    floor /= i;
                }
            }
            if (answer.empty())
                answer.push_back(number);
        }
        std::for_each(answer.cbegin(), answer.cend(), [](auto e) {
            std::cout << e << " ";
        });
        std::cout << std::endl;
    }
    return 0;
}
#endif

// 最优解
#if 1
auto main(int argc, char* argv[]) -> int
{
    unsigned long number {};
    while (std::cin >> number) {
        std::vector<unsigned long> answer {};
        if (number <= 2)
            answer.push_back(number);
        else {
            unsigned long floor = number;
            for (size_t i = 2; i * i <= floor; ++i) { // #1
                while (0 == floor % i) {
                    answer.push_back(i);
                    floor /= i;
                }
            }
            if (1 != floor) // #2
                answer.push_back(floor);
            if (answer.empty())
                answer.push_back(number);
        }
        std::for_each(answer.cbegin(), answer.cend(), [](auto e) {
            std::cout << e << " ";
        });
        std::cout << std::endl;
    }
    return 0;
}
#endif

#if 0
2000000014
#endif