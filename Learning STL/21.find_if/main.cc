#include <algorithm>
#include <iostream>
#include <vector>

auto main(int argc, char* argv[]) -> int
{
    std::vector vi { 1, 2, 2, 3, 3, 3, 4, 4, 4, 4 };
    auto it = std::find_if(vi.cbegin(), vi.cend(), [](auto e) { return e * e == 4; });
    std::cout << it - vi.cbegin() << std::endl;
    return 0;
}