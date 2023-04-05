// HJ8 合并表记录
#include <algorithm>
#include <iostream>
#include <map>

#if 1
auto main(int argc, char* argv[]) -> int
{
    size_t n;
    std::map<unsigned int, unsigned int> dict {};
    while (std::cin >> n) {
        unsigned int index, value {};
        for (size_t i = 1; i <= n; ++i) {
            std::cin >> index >> value;
            auto it = dict.find(index);
            if (it != dict.end())
                it->second += value;
            else
                dict.insert(std::pair(index, value));
        }
        std::for_each(dict.cbegin(), dict.cend(), [](auto e) {
            std::cout << e.first << " " << e.second << std::endl;
        });
    }
    return 0;
}
#endif

#if 0
std::map.find(index) 返回的是it 使用it->first, it->second进行修改
std::for_each(map.cbegin(), map.cend(), [](auto e){}) e是const std::pair, 使用e.fisrt, e.second访问其值
#endif