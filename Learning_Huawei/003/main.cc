// HJ3 明明的随机数
#include <algorithm>
#include <iostream>
#include <set>

#if 1
auto main(int argc, char* argv[]) -> int
{
    constexpr size_t MIN_SIZE = 1;
    constexpr size_t MAX_SIZE = 1000;
    size_t n {};
    while (std::cin >> n && MIN_SIZE <= n && n <= MAX_SIZE) {
        int number {};
        std::set<int> hash {};
        for (size_t i = 1; i <= n; ++i) {
            std::cin >> number;
            if (1 <= number && number <= 500)
                hash.insert(number);
            // std::cin.clear();
            // std::cin.sync();
        }
        std::for_each(hash.cbegin(), hash.cend(), [](auto e) {
            std::cout << e << std::endl;
        });
    }
    return 0;
}
#endif