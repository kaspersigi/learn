#include <iostream>
#include <vector>

std::vector<std::vector<int>> generate_matrix(int n)
{
    std::vector<std::vector<int>> vii(n, std::vector<int>(n, 0));
    int num = 1;
    int top = 0, bottom = n - 1, left = 0, right = n - 1;

    while (top <= bottom && left <= right) {
        // top row: left -> right
        for (int col = left; col <= right; ++col) {
            vii[top][col] = num++;
        }
        top++;

        // right column: top -> bottom
        for (int row = top; row <= bottom; ++row) {
            vii[row][right] = num++;
        }
        right--;

        // bottom row: right -> left (if exists)
        if (top <= bottom) {
            for (int col = right; col >= left; --col) {
                vii[bottom][col] = num++;
            }
            bottom--;
        }

        // left column: bottom -> top (if exists)
        if (left <= right) {
            for (int row = bottom; row >= top; --row) {
                vii[row][left] = num++;
            }
            left++;
        }
    }
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