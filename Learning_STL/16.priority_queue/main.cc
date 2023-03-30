#include <iostream>
#include <queue>

auto main(int argc, char* argv[]) -> int
{
    std::priority_queue<int> nums; // 无法以初始化列表进行初始化
    nums.push(1);
    nums.push(3);
    nums.push(2);
    nums.push(2);
    nums.push(7);
    nums.push(5);
    nums.push(6);
    nums.push(1);
    nums.push(1);
    nums.push(2);
    nums.push(2);

    // std::for_each(nums.cbegin(), nums.cend(), [](auto e) { std::cout << e << " "; });
    // std::cout << std::endl;
    // 没有这种迭代器

    while (!nums.empty()) {
        std::cout << nums.top() << std::endl;
        nums.pop();
    }

    // 有点类似栈，默认最大的在栈顶

    return 0;
}