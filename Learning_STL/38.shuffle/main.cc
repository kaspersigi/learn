#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

int main()
{
    std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // 使用随机数引擎打乱
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(v.begin(), v.end(), g);

    std::cout << "Shuffled: ";
    for (int x : v)
        std::cout << x << " ";
    std::cout << "\n";

    // ✅ 学习点：现代 C++ 推荐替代 std::random_shuffle（已弃用）
}