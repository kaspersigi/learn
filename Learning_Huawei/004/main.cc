// HJ4 字符串分割
#include <iostream>
#include <string>
extern "C" {
#include <string.h>
}

#if 1
auto main(int argc, char* argv[]) -> int
{
    constexpr size_t MAX_SIZE = 101;
    char buffer[MAX_SIZE] = {};
    char tail[8] = {};
    while (std::cin.getline(buffer, MAX_SIZE)) {
        std::string str = std::string(buffer);
        if (!str.empty()) {
            std::string substr {};
            size_t floor = str.length() % 8;
            if (floor) {
                for (size_t i = 0; i < 8 - floor; ++i)
                    tail[i] = '0';
                str.append(tail);
            }
            for (size_t i = 0; i < str.length() / 8; ++i) {
                substr = str.substr(i * 8, 8);
                std::cout << substr << std::endl;
            }
        }
        memset(buffer, 0, MAX_SIZE);
        memset(tail, 0, 8);
    }
    return 0;
}
#endif