#include <iostream>
#include <stack>

auto main(int argc, char* argv[]) -> int
{
    std::stack<int> nums; // 无法以初始化列表进行初始化
    nums.push(1);
    nums.push(2);
    nums.push(3);

    // std::for_each(nums.cbegin(), nums.cend(), [](auto e) { std::cout << e << " "; });
    // std::cout << std::endl;
    // 没有这种迭代器

    while (!nums.empty()) {
        std::cout << nums.top() << std::endl;
        nums.pop();
    }

    return 0;
}