#include <algorithm>
#include <iostream>
#include <vector>

#if 0
// 暴力破解，双循环，O(n+nlogn)
std::vector<int> sorted_squares(std::vector<int>& A)
{
    std::vector<int> vi {};
    std::for_each(A.cbegin(), A.cend(), [&](auto e) { vi.push_back(e * e); });
    std::sort(vi.begin(), vi.end());
    return vi;
}
#endif

#if 1
// 快慢指针，单循环，O(n)
std::vector<int> sorted_squares(std::vector<int>& A)
{
    std::vector<int> vi(A.size(), 0);
    size_t slow {};
    size_t fast { A.size() - 1 };
    size_t pos { A.size() - 1 };
    while (slow <= fast) {
        if (A[fast] * A[fast] > A[slow] * A[slow]) {
            vi[pos] = A[fast] * A[fast];
            --fast;
        } else {
            vi[pos] = A[slow] * A[slow];
            ++slow;
        }
        pos--;
    }
    return vi;
}
#endif

auto main(int argc, char* argv[]) -> int
{
    std::vector<int> vi { -4, -1, 0, 3, 10 };
    auto v = sorted_squares(vi);
    std::for_each(v.cbegin(), v.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;

    return 0;
}