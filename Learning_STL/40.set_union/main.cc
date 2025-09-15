#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> a = { 1, 2, 3, 4, 5 };
    std::vector<int> b = { 3, 4, 5, 6, 7 };

    // 必须先排序（已满足）

    std::vector<int> uni(a.size() + b.size());
    std::vector<int> inter(a.size() + b.size());

    // 并集
    auto uni_end = std::set_union(a.begin(), a.end(),
        b.begin(), b.end(),
        uni.begin());
    uni.resize(std::distance(uni.begin(), uni_end));

    // 交集
    auto inter_end = std::set_intersection(a.begin(), a.end(),
        b.begin(), b.end(),
        inter.begin());
    inter.resize(std::distance(inter.begin(), inter_end));

    std::cout << "Union: ";
    for (int x : uni)
        std::cout << x << " "; // 1 2 3 4 5 6 7

    std::cout << "\nIntersection: ";
    for (int x : inter)
        std::cout << x << " "; // 3 4 5
    std::cout << "\n";

    // ✅ 学习点：数学集合操作，函数式中“集合代数”
}