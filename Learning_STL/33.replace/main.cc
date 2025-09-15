#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v = { 1, 2, 3, 2, 4, 2 };

    // replace：把所有 2 替换成 99
    std::replace(v.begin(), v.end(), 2, 99);

    std::cout << "After replace: ";
    for (int x : v)
        std::cout << x << " "; // 1 99 3 99 4 99
    std::cout << "\n";

    // replace_if：把所有偶数替换成 0
    std::replace_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; }, 0);

    std::cout << "After replace_if (evens→0): ";
    for (int x : v)
        std::cout << x << " "; // 1 0 3 0 0 0
    std::cout << "\n";

    // ✅ 学习点：replace_if 是“条件更新”，函数式中类似 map + condition
}