#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8 };

    // partition：把所有偶数移到前面，奇数移到后面（不保证内部顺序）
    auto pivot = std::partition(v.begin(), v.end(), [](int x) {
        return x % 2 == 0; // 偶数放前面
    });

    std::cout << "Partitioned: ";
    for (int x : v)
        std::cout << x << " ";
    std::cout << "\n";
    // 可能输出：8 2 6 4 5 3 7 1 （顺序不保证，但偶数都在奇数前）

    std::cout << "Pivot at index: " << std::distance(v.begin(), pivot) << "\n"; // 指向第一个奇数

    // ✅ 学习点：快速排序的核心步骤，函数式中类似“分组”
}