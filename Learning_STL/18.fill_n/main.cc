#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v(5, 0); // {0,0,0,0,0}

    std::fill_n(v.begin(), 3, -1); // 前3个设为 -1

    for (int x : v)
        std::cout << x << " "; // 输出: -1 -1 -1 0 0
    std::cout << "\n";

    // ✅ 学习点：从迭代器开始填 N 个，注意不要越界！
}