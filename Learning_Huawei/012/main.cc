// HJ12 字符串反转
#include <algorithm>
#include <iostream>
#include <string>
extern "C" {
#include <string.h>
}

#if 1
auto main(int argc, char* argv[]) -> int
{
    constexpr size_t MAX_SIZE = 1001;
    char buffer[MAX_SIZE] = {};
    while (std::cin.getline(buffer, MAX_SIZE)) {
        std::string str = std::string(buffer);
        std::string answer {};
        std::for_each(str.crbegin(), str.crend(), [&](auto e) { answer.push_back(e); });
        std::cout << answer << std::endl;
        memset(buffer, 0, MAX_SIZE);
    }
    return 0;
}
#endif