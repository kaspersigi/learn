// HJ9 提取不重复的整数
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>

#if 1
auto main(int argc, char* argv[]) -> int
{
    int n;
    while (std::cin >> n) {
        std::string str = std::to_string(n);
        std::unordered_set<char> hash {};
        std::for_each(str.cbegin(), str.cend(), [&](auto e) { hash.insert(e); });
        std::for_each(str.crbegin(), str.crend(), [&](auto e) { if(hash.end()!=hash.find(e)) {std::cout << e; hash.erase(e);} });
        std::cout << std::endl;
    }
    return 0;
}
#endif

#if 0
int转std::string std::to_string(n)
std::string转int std::stoi(str)
#endif