#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v = { 1, 3, 3, 3, 5, 7, 9 };
    // ⚠️ 必须已排序！

    // binary_search：只返回 bool，是否存在
    bool found = std::binary_search(v.begin(), v.end(), 3);
    std::cout << "3 exists? " << std::boolalpha << found << "\n"; // true

    // lower_bound：返回第一个 >= value 的迭代器
    auto it_low = std::lower_bound(v.begin(), v.end(), 3);
    std::cout << "First 3 at index: " << std::distance(v.begin(), it_low) << "\n"; // 1

    // upper_bound：返回第一个 > value 的迭代器
    auto it_up = std::upper_bound(v.begin(), v.end(), 3);
    std::cout << "After last 3 at index: " << std::distance(v.begin(), it_up) << "\n"; // 4

    // equal_range：返回 [lower, upper) 范围
    auto range = std::equal_range(v.begin(), v.end(), 3);
    std::cout << "Count of 3s: " << std::distance(range.first, range.second) << "\n"; // 3

    // ✅ 学习点：二分查找前提是有序！lower_bound 是“插入位置”算法
}