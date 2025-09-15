#include <iostream>
#include <numeric> // 注意：accumulate 在 <numeric> 不是 <algorithm>
#include <vector>

int main()
{
    std::vector<int> v = { 1, 2, 3, 4, 5 };

    // 求和
    int sum = std::accumulate(v.begin(), v.end(), 0);
    std::cout << "Sum: " << sum << "\n"; // 输出: 15

    // 自定义操作：求积
    int product = std::accumulate(v.begin(), v.end(), 1, [](int a, int b) {
        return a * b;
    });
    std::cout << "Product: " << product << "\n"; // 输出: 120

    // ✅ 学习点：函数式中的“reduce/fold”
    // ✅ 初始值 + 二元操作符
}