#include <iostream>
#include <vector>

std::vector<std::vector<int>> generate_matrix(int n)
{
    std::vector<std::vector<int>> vii(n, std::vector<int>(n, 0));

    return vii;
}

auto main(int argc, char* argv[]) -> int
{
    int n = 5;
    auto vii = generate_matrix(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << vii[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    return 0;
}