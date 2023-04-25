#include <algorithm>
#include <iostream>
#include <vector>

std::vector<int> sorted_squares(std::vector<int>& A)
{
    std::vector<int> vi {};
    int pos = -1;
    for (int i = 0; i < A.size(); ++i) {
        if (A[i] < 0) {
            pos = i;
        } else
            break;
    }
    if (-1 == pos) {
        std::for_each(A.cbegin(), A.cend(), [&](auto e) { vi.push_back(e * e); });
    } else if (A.size() - 1 == pos) {
        std::for_each(A.crbegin(), A.crend(), [&](auto e) { vi.push_back(e * e); });
    } else {
    }
    return vi;
}

auto main(int argc, char* argv[]) -> int
{
    // std::vector<int> vi { -4, -1, 0, 3, 10 };
    // std::vector<int> vi { 0, 3, 10 };
    std::vector<int> vi { -10, -3, -1 };
    auto v = sorted_squares(vi);
    std::for_each(v.cbegin(), v.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;

    return 0;
}