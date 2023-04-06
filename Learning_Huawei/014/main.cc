// HJ14 字符串排序
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
extern "C" {
#include <string.h>
}

#if 1
auto main(int argc, char* argv[]) -> int
{
    size_t n {};
    std::string word {};
    while (std::cin >> n) {
        std::multiset<std::string> hash {};
        for (size_t i = 1; i <= n; ++i) {
            std::cin >> word;
            hash.insert(word);
        }
        std::for_each(hash.cbegin(), hash.cend(), [](auto e) { std::cout << e << std::endl; });
    }
    return 0;
}
#endif