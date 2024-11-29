#include <algorithm>
#include <iostream>
#include <map>

auto main(int argc, char* argv[]) -> int
{
    std::map dict {
        std::pair('a', 1),
        std::pair('b', 2),
        std::pair('c', 3),
        std::pair('d', 4),
        std::pair('e', 5),
        std::pair('f', 6),
        std::pair('g', 7),
    };

    std::for_each(dict.cbegin(), dict.cend(), [](auto e) { std::cout << e.first << " " << e.second << std::endl; });
    std::cout << std::endl;

    auto it = dict.find('c');
    dict.erase(it);

    std::for_each(dict.cbegin(), dict.cend(), [](auto e) { std::cout << e.first << " " << e.second << std::endl; });
    std::cout << std::endl;

    dict.insert(std::pair('c', 3));

    std::for_each(dict.cbegin(), dict.cend(), [](auto e) { std::cout << e.first << " " << e.second << std::endl; });
    std::cout << std::endl;

    auto node = dict.extract('c');
    node.key() = 'h';
    dict.insert(std::move(node));
    std::for_each(dict.cbegin(), dict.cend(), [](auto e) { std::cout << e.first << " " << e.second << std::endl; });
    std::cout << std::endl;

    auto e = dict.find('f');
    std::cout << e->first << " " << e->second << std::endl;
    std::cout << std::endl;
    // e->first = 'z'; // 不能直接修改key
    e->second = 100;
    std::for_each(dict.cbegin(), dict.cend(), [](auto e) { std::cout << e.first << " " << e.second << std::endl; });

    return 0;
}