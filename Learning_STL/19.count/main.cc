#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v = { 1, 2, 3, 2, 4, 2 };

    size_t cnt = std::count(v.begin(), v.end(), 2);

    std::cout << "Number of 2s: " << cnt << "\n"; // 输出: 3

    // ✅ 学习点：比较使用 operator==，适用于任何可比较类型
}