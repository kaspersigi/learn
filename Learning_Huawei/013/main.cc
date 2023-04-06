// HJ13 句子逆序
#include <algorithm>
#include <iostream>
#include <string>

#if 0
auto main(int argc, char* argv[]) -> int
{
    std::string word {};
    while (std::cin >> word) {
        std::vector<std::string> vs {};
        vs.push_back(word);
        std::for_each(vs.cbegin(), vs.cend(), [](auto e) { std::cout << e << " "; });
        std::cout << std::endl;
    }
    return 0;
}
#endif

#if 1
extern "C" {
#include <string.h>
}
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

#if 0
如何对std::string做split?
std::cin //不太行
std::istringstream
std::regex
#endif