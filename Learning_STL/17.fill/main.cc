#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v(5); // {0,0,0,0,0}

    std::fill(v.begin(), v.end(), 99); // 全部设为 99

    for (int x : v)
        std::cout << x << " "; // 输出: 99 99 99 99 99
    std::cout << "\n";

    // ✅ 学习点：范围 [first, last)，值类型需可赋值
}