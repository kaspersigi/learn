#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> src = { 1, -2, 3, -4, 5, -6 };
    std::vector<int> positive;

    // 预留空间（或用 back_inserter）
    positive.resize(src.size()); // 临时方案，实际推荐用 inserter

    // 方法1：copy_if + 手动 resize
    auto end_it = std::copy_if(src.begin(), src.end(), positive.begin(), [](int x) {
        return x > 0;
    });
    positive.resize(std::distance(positive.begin(), end_it));

    // 方法2（推荐）：使用 back_inserter（需 #include <iterator>）
    // std::vector<int> positive;
    // std::copy_if(src.begin(), src.end(), std::back_inserter(positive), [](int x){ return x > 0; });

    for (int x : positive)
        std::cout << x << " "; // 输出: 1 3 5
    std::cout << "\n";

    // ✅ 学习点：copy_if 是“filter”操作
    // ✅ 结合 inserter 可动态插入，避免预分配
}