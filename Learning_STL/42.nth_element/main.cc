#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v = { 9, 3, 7, 1, 8, 2, 6, 4, 5 };

    // 使第4个元素（索引3）是排序后应在的位置，左边≤它，右边≥它
    std::nth_element(v.begin(), v.begin() + 3, v.end());

    std::cout << "After nth_element (4th smallest at index 3):\n";
    for (int x : v)
        std::cout << x << " ";
    std::cout << "\nElement at index 3: " << v[3] << "\n"; // 应该是第4小的数（从1数起）

    // ✅ 学习点：O(n) 找中位数或分位数，比排序快
    // ✅ 常用于找中位数：nth_element(v.begin(), v.begin() + v.size()/2, v.end());
}