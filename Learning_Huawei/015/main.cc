// HJ15 求int型正整数在内存中存储时1的个数
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <unordered_map>

std::unordered_map<char, size_t> hash {
    std::pair('0', 0),
    std::pair('1', 1),
    std::pair('2', 1),
    std::pair('3', 2),
    std::pair('4', 1),
    std::pair('5', 2),
    std::pair('6', 2),
    std::pair('7', 3)
};

#if 1
auto main(int argc, char* argv[]) -> int
{
    int n {};
    while (std::cin >> n) {
        std::stringstream ss;
        size_t answer {};
        ss << std::oct << n;
        auto str = ss.str();
        std::for_each(str.cbegin(), str.cend(), [&](auto e) { auto it = hash.find(e); answer+=it->second; });
        std::cout << answer << std::endl;
    }
    return 0;
}
#endif

#if 0
本打算使用c++流算子，直接进行进制转换，但是，流算子只支持8、10、16进制
#endif