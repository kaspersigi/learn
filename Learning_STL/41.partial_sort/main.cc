#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v = { 9, 3, 7, 1, 8, 2, 6, 4, 5 };

    // 将前 3 个最小元素排序放在开头，其余无序
    std::partial_sort(v.begin(), v.begin() + 3, v.end());

    std::cout << "After partial_sort (top 3 min): ";
    for (int x : v)
        std::cout << x << " ";
    // 输出：1 2 3 ? ? ? ? ? ? （前3有序，其余任意）

    std::cout << "\nTop 3: " << v[0] << ", " << v[1] << ", " << v[2] << "\n"; // 1, 2, 3

    // ✅ 学习点：比全排序高效，适合“找 Top-K”场景
}