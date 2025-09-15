#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

int main()
{
    std::vector<int> v(5);

    // 用随机数生成器填充
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    std::generate(v.begin(), v.end(), [&]() { return dis(gen); });

    std::cout << "Random generated: ";
    for (int x : v)
        std::cout << x << " ";
    std::cout << "\n";

    // generate_n：只生成前 N 个
    std::vector<int> v2(10, 0);
    std::generate_n(v2.begin(), 3, [&]() { return dis(gen); }); // 只填前3个

    std::cout << "First 3 random: ";
    for (int x : v2)
        std::cout << x << " "; // 后7个仍是0
    std::cout << "\n";

    // ✅ 学习点：函数式“生成器”模式，每次调用函数产生新值
}