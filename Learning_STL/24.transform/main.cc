#include <algorithm>
#include <iostream>
#include <vector>

auto main(int argc, char* argv[]) -> int
{
    std::vector input {
        1,
        2,
        3,
        4,
        5,
        6,
        7,
        8,
        9,
        10,
    };
    decltype(input) result(input.size());
    std::transform(input.cbegin(), input.cend(), result.begin(), [](int e) { return e * 2; });
    std::for_each(result.cbegin(), result.cend(), [](auto e) { std::cout << e << " "; });
    // std::copy(result.cbegin(), result.cend(), std::ostream_iterator<std::string>(std::cout, "\n"));
    return 0;
}