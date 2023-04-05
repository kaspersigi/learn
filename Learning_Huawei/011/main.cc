// HJ11 数字颠倒
#include <algorithm>
#include <iostream>
#include <string>

#if 1
auto main(int argc, char* argv[]) -> int
{
    int n;
    while (std::cin >> n) {
        std::string str = std::to_string(n);
        std::string answer {};
        std::for_each(str.crbegin(), str.crend(), [&](auto e) { answer.push_back(e); });
        std::cout << answer << std::endl;
    }
    return 0;
}
#endif