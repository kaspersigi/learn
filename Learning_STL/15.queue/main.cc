#include <iostream>
#include <queue>

auto main(int argc, char* argv[]) -> int
{
    std::queue<int> nums; // 无法以初始化列表进行初始化
    nums.push(1);
    nums.push(2);
    nums.push(3);

    // std::for_each(nums.cbegin(), nums.cend(), [](auto e) { std::cout << e << " "; });
    // std::cout << std::endl;
    // 没有这种迭代器

    while (!nums.empty()) {
        std::cout << nums.front() << std::endl;
        nums.pop();
    }

    // nums.back(); //访问队列中的最后一个元素

    return 0;
}