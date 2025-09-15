#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v = { 1, 1, 2, 2, 2, 3, 4, 4, 5 };

    // unique 只移除“相邻”重复元素！
    auto new_end = std::unique(v.begin(), v.end());

    // 真正删除尾部
    v.erase(new_end, v.end());

    std::cout << "Unique: ";
    for (int x : v)
        std::cout << x << " "; // 输出: 1 2 3 4 5
    std::cout << "\n";

    // ❗ 如果不相邻，先 sort！
    std::vector<int> v2 = { 3, 1, 4, 1, 5, 9, 2, 6, 5 };
    std::sort(v2.begin(), v2.end()); // 必须先排序
    auto it = std::unique(v2.begin(), v2.end());
    v2.erase(it, v2.end());

    std::cout << "Sorted + Unique: ";
    for (int x : v2)
        std::cout << x << " "; // 1 2 3 4 5 6 9
    std::cout << "\n";

    // ✅ 学习点：unique 只处理“连续重复”，常与 sort 配合使用
}