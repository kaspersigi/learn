#include <algorithm>
#include <iostream>
#include <vector>

auto main(int argc, char* argv[]) -> int
{
    std::vector vi { 1, 2, 2, 3, 3, 3, 4, 4, 4, 4 };
    auto it = std::search_n(vi.cbegin(), vi.cend(), 3, 4);
    std::cout << std::distance(vi.cbegin(), it) << std::endl;

    decltype(vi) vo { 4, 4 };
    auto it2 = std::search(vi.cbegin(), vi.cend(), vo.cbegin(), vo.cend());
    std::cout << std::distance(vi.cbegin(), it2) << std::endl;

    auto it3 = std::find_end(vi.cbegin(), vi.cend(), vo.cbegin(), vo.cend());
    std::cout << std::distance(vi.cbegin(), it3) << std::endl;

    auto it4 = std::find_first_of(vi.cbegin(), vi.cend(), vo.cbegin(), vo.cend());
    std::cout << std::distance(vi.cbegin(), it4) << std::endl;

    auto it5 = std::adjacent_find(vi.cbegin(), vi.cend());
    std::cout << std::distance(vi.cbegin(), it5) << std::endl;

    return 0;
}