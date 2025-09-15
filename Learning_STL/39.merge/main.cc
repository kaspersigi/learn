#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v1 = { 1, 3, 5, 7 };
    std::vector<int> v2 = { 2, 4, 6, 8 };
    std::vector<int> result(v1.size() + v2.size());

    std::merge(v1.begin(), v1.end(),
        v2.begin(), v2.end(),
        result.begin());

    std::cout << "Merged: ";
    for (int x : result)
        std::cout << x << " "; // 1 2 3 4 5 6 7 8
    std::cout << "\n";

    // ✅ 学习点：归并排序的核心，函数式中“combine sorted streams”
    // ✅ 要求输入已排序，输出也排序
}