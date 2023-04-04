// HJ8 合并表记录
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
    std::string answer {};
    while (std::cin.getline(buffer, MAX_SIZE)) {
        std::string str = std::string(buffer);
        answer = str;
        std::cout << answer << std::endl;
        memset(buffer, 0, MAX_SIZE);
    }
    return 0;
}
#endif