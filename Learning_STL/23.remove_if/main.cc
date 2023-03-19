#include <algorithm>
#include <iostream>
#include <vector>

auto main(int argc, char* argv[]) -> int
{
    std::vector vi { 1, 2, 2, 3, 3, 3, 4, 4, 4, 4 };
    std::cout << vi.size() << std::endl;
    auto it = std::remove_if(vi.begin(), vi.end(), [](auto e) { return e * e == 4; });
    for (size_t i = 0; i < vi.size(); i++)
        std::cout << vi[i] << " ";
    std::cout << std::endl;
    std::cout << vi.size() << std::endl;
    // for_each(vi.cbegin(), vi.cend(), [](auto e) { std::cout << e << " "; });
    return 0;
}