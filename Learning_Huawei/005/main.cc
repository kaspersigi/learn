// HJ5 进制转换
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
extern "C" {
#include <string.h>
}

#if 1
std::unordered_map<char, int> const map {
    std::pair('0', 0),
    std::pair('1', 1),
    std::pair('2', 2),
    std::pair('3', 3),
    std::pair('4', 4),
    std::pair('5', 5),
    std::pair('6', 6),
    std::pair('7', 7),
    std::pair('8', 8),
    std::pair('9', 9),
    std::pair('A', 10),
    std::pair('a', 10),
    std::pair('B', 11),
    std::pair('b', 11),
    std::pair('C', 12),
    std::pair('c', 12),
    std::pair('D', 13),
    std::pair('d', 13),
    std::pair('E', 14),
    std::pair('e', 14),
    std::pair('F', 15),
    std::pair('f', 15)
};

unsigned int power_of_16(unsigned int power)
{
    size_t ret = 1;
    if (power > 0) {
        for (size_t i = 0; i < power; ++i)
            ret *= 16;
    }
    return ret;
}

auto main(int argc, char* argv[]) -> int
{
    constexpr size_t MAX_SIZE = 35;
    char buffer[MAX_SIZE] = {};
    std::string str {};
    unsigned int answer {};
    while (std::cin.getline(buffer, MAX_SIZE)) {
        if ('0' == buffer[0] && 'x' == buffer[1]) {
            str = std::string(buffer + 2);
            std::string rstr {};
            std::for_each(str.crbegin(), str.crend(), [&](auto e) {
                rstr.push_back(e);
            });
            for (size_t i = 0; i < rstr.length(); ++i) {
                unsigned int temp = power_of_16(i) * (map.find(rstr[i])->second);
                answer += temp;
            }
            std::cout << answer << std::endl;
        }
        memset(buffer, 0, MAX_SIZE);
        answer = 0;
    }
    return 0;
}
#endif

#if 0
搞清楚string.append()和string.push_back()的区别
std::string const str = "123456789";
std::string rstr {};
std::for_each(str.crbegin(), str.crend(), [&](auto e) {
    rstr.push_back(e);
});
std::cout << rstr << std::endl;
#endif