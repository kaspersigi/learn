#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v = { 5, 2, 8, 1, 9 };

    std::sort(v.begin(), v.end()); // 默认升序

    std::cout << "Sorted: ";
    for (int x : v)
        std::cout << x << " "; // 输出: 1 2 5 8 9
    std::cout << "\n";

    // 降序：传入比较谓词
    std::sort(v.begin(), v.end(), [](int a, int b) {
        return a > b; // 降序
    });

    std::cout << "Descending: ";
    for (int x : v)
        std::cout << x << " "; // 输出: 9 8 5 2 1
    std::cout << "\n";

    // ✅ 学习点：默认 operator<，可自定义比较函数（函数式：行为参数化）
}