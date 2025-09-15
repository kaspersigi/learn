#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v = { 1, 2, 3, 4, 5 };

    // 打印每个元素（带副作用，仅演示）
    std::for_each(v.begin(), v.end(), [](int x) {
        std::cout << x * x << " "; // 输出: 1 4 9 16 25
    });
    std::cout << "\n";

    // ✅ 学习点：最接近“函数式遍历”的算法
    // ✅ 注意：C++20 后更推荐用 range-for，但 for_each 在组合算法时仍有价值
}