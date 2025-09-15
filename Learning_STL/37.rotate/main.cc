#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v = { 1, 2, 3, 4, 5 };

    // 把 [begin, mid) 旋转到末尾，[mid, end) 旋转到开头
    std::rotate(v.begin(), v.begin() + 2, v.end());
    // 原：1 2 | 3 4 5 → 新：3 4 5 1 2

    std::cout << "Rotated: ";
    for (int x : v)
        std::cout << x << " "; // 输出: 3 4 5 1 2
    std::cout << "\n";

    // ✅ 学习点：高效块移动，常用于队列/环形缓冲区操作
}