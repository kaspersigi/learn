// HJ10 字符个数统计
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
extern "C" {
#include <string.h>
}

#if 1
auto main(int argc, char* argv[]) -> int
{
    constexpr size_t MAX_SIZE = 501;
    char buffer[MAX_SIZE] = {};
    while (std::cin.getline(buffer, MAX_SIZE)) {
        std::string str = std::string(buffer);
        std::unordered_set<char> hash {};
        std::for_each(str.cbegin(), str.cend(), [&](auto e) { hash.insert(e); });
        std::cout << hash.size() << std::endl;
        memset(buffer, 0, MAX_SIZE);
    }
    return 0;
}
#endif