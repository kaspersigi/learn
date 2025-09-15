#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v = { 1, 2, 3, 4, 5, 6 };

    // remove_if 不真删除，只移动元素，返回新逻辑结尾
    auto new_end = std::remove_if(v.begin(), v.end(), [](int x) {
        return x % 2 == 0; // 移除偶数
    });

    // 真正删除尾部“无效”元素
    v.erase(new_end, v.end());

    for (int x : v)
        std::cout << x << " "; // 输出: 1 3 5
    std::cout << "\n";

    // ✅ 学习点：STL 中“移除”算法的通用模式
    // ✅ 必须配合 erase 才能真正缩小容器
}