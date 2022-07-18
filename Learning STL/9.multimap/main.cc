#include <algorithm>
#include <iostream>
#include <map>

auto main(int argc, char* argv[]) -> int
{
    std::multimap dict {
        std::pair('a', 1),
        std::pair('b', 2),
        std::pair('b', 3),
        std::pair('c', 4),
        std::pair('c', 5),
        std::pair('c', 6),
        std::pair('d', 7),
        std::pair('d', 8),
        std::pair('d', 9),
        std::pair('d', 10)
    };

    std::for_each(dict.cbegin(), dict.cend(), [](auto e) { std::cout << e.first << " " << e.second << std::endl; });
    std::cout << std::endl;

    auto it = dict.find('c');
    dict.erase(it);

    std::for_each(dict.cbegin(), dict.cend(), [](auto e) { std::cout << e.first << " " << e.second << std::endl; });
    std::cout << std::endl;

    dict.insert(std::pair('c', 4));

    std::for_each(dict.cbegin(), dict.cend(), [](auto e) { std::cout << e.first << " " << e.second << std::endl; });
    std::cout << std::endl;

    dict.erase('c');

    std::for_each(dict.cbegin(), dict.cend(), [](auto e) { std::cout << e.first << " " << e.second << std::endl; });
    std::cout << std::endl;

    auto node = dict.extract('d');
    node.key() = 'c';
    dict.insert(std::move(node));
    std::for_each(dict.cbegin(), dict.cend(), [](auto e) { std::cout << e.first << " " << e.second << std::endl; });
    std::cout << std::endl;

    std::cout << dict.count('d') << std::endl;

    return 0;
}