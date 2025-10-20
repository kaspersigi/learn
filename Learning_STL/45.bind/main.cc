#include <algorithm>
#include <functional> // std::bind, std::function
#include <iostream>
#include <vector>

bool is_divisible_by(int x, int divisor)
{
    return x % divisor == 0;
}

int main()
{
    std::vector<int> v = { 10, 15, 20, 25, 30, 35 };

    // 绑定 divisor=5，生成新谓词
    auto is_div_by_5 = std::bind(is_divisible_by, std::placeholders::_1, 5);

    size_t count = std::count_if(v.begin(), v.end(), is_div_by_5);
    std::cout << "Divisible by 5: " << count << "\n"; // 6

    // 用 std::function 存储
    std::function<bool(int)> pred = is_div_by_5;
    count = std::count_if(v.begin(), v.end(), pred);
    std::cout << "Same with std::function: " << count << "\n";

    // ✅ 学习点：函数适配器，实现参数绑定、复用、存储
    // ✅ 类似函数式中的“部分应用”或“柯里化”
}