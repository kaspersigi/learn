#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v = { 1, 2, 3, 4, 5 };
    std::vector<int> result(v.size());

    // 平方每个元素
    std::transform(v.begin(), v.end(), result.begin(), [](int x) {
        return x * x;
    });

    for (int x : result)
        std::cout << x << " "; // 输出: 1 4 9 16 25
    std::cout << "\n";

    // ✅ 学习点：函数式中的“map”操作
    // ✅ 输入范围 → 输出范围，一对一变换
}