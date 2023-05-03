#include <iostream>
#include <vector>

enum direction { up,
    right,
    down,
    left };

std::vector<std::vector<int>> generate_matrix(int n)
{
    std::vector<std::vector<int>> vii(n, std::vector<int>(n, 0));
    size_t row {};
    size_t column {};
    size_t layer {};
    enum direction dir { direction::up };
    size_t num = 1;
    while (n % 2 == 1 ? num < n * n : num <= n * n) {
        switch (dir) {
        case direction::up:
            for (int i = 0; i < n - layer * 2 - 1; ++i) {
                row = layer;
                column = i + layer;
                vii[row][column] = num++;
            }
            break;
        case direction::right:
            for (int i = 0; i < n - layer * 2 - 1; ++i) {
                row = i + layer;
                column = n - layer - 1;
                vii[row][column] = num++;
            }
            break;
        case direction::down:
            for (int i = 0; i < n - layer * 2 - 1; ++i) {
                row = n - layer - 1;
                column = n - i - 1 - layer;
                vii[row][column] = num++;
            }
            break;
        case direction::left:
            for (int i = 0; i < n - layer * 2 - 1; ++i) {
                row = n - i - layer - 1;
                column = layer;
                vii[row][column] = num++;
            }
            ++layer;
            break;
        }
        dir = direction((dir + 1) % 4);
    }
    if (n % 2 == 1)
        vii[layer][layer] = n * n;
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