#include <algorithm>
#include <iostream>
#include <vector>

std::vector<std::vector<int>> three_sum(std::vector<int>& nums)
{
    std::vector<std::vector<int>> vii {};
    return vii;
}

auto main(int argc, char* argv[]) -> int
{
    std::vector<int> vi { -1, 0, 1, 2, -1, -4 };
    auto vii = three_sum(vi);
    for (auto const& row : vii) {
        for (auto const& e : row) {
            std::cout << e << "\t";
        }
        std::cout << std::endl;
    }
    return 0;
}