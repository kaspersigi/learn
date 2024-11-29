#include <algorithm>
#include <iostream>
#include <vector>

auto main(int argc, char* argv[]) -> int
{
    std::vector vi {
        1,
        2,
        2,
        3,
        3,
        3,
        4,
        4,
        4,
        4,
    };
    decltype(vi) vo(10);
    auto it = std::copy_if(vi.cbegin(), vi.cend(), vo.begin(), [](auto e) { return e * e == 4; });
    vo.resize(std::distance(vo.begin(), it));
    for_each(vo.cbegin(), vo.cend(), [](auto e) { std::cout << e << " "; });
    return 0;
}