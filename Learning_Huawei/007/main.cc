// HJ7 取近似值
#include <iostream>

// 明确为正浮点数
#if 1
auto main(int argc, char* argv[]) -> int
{
    int answer {};
    double number {};
    while (std::cin >> number) {
        answer = (number + 0.5) * 10 / 10;
        std::cout << answer << std::endl;
    }
    return 0;
}
#endif