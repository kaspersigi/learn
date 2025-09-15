#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v = { 1, 2, 2, 3, 4, 4, 5 };

    // 找第一个相邻相等的元素
    auto it = std::adjacent_find(v.begin(), v.end());
    if (it != v.end()) {
        std::cout << "First adjacent duplicate: " << *it << " at index "
                  << std::distance(v.begin(), it) << "\n"; // 2 at index 1
    }

    // 自定义：找第一个相邻递减对
    auto it2 = std::adjacent_find(v.begin(), v.end(), [](int a, int b) {
        return a > b; // 前一个 > 后一个
    });
    if (it2 != v.end()) {
        std::cout << "First decreasing pair starts at: " << *it2 << "\n";
    }

    // ✅ 学习点：滑动窗口大小=2，函数式中“pair-wise operation”
}