#include <algorithm>
#include <iostream>
#include <vector>

auto main(int argc, char* argv[]) -> int
{
    std::vector nums {
        1,
        0,
        2,
        3,
        0,
        4,
        5,
        6,
        0,
        7,
        8,
        9,
    };
    std::cout << nums.size() << std::endl;
    std::cout << nums.capacity() << std::endl;
    std::cout << nums.max_size() << std::endl;

    std::for_each(nums.cbegin(), nums.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;

    // audo no_space_end = std::remove(nums.begin(), nums.end(), 0);
    nums.erase(std::remove(nums.begin(), nums.end(), 0), nums.end());
    std::for_each(nums.cbegin(), nums.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;

    std::cout << nums.size() << std::endl;
    std::cout << nums.capacity() << std::endl;
    std::cout << nums.max_size() << std::endl;

    nums.shrink_to_fit();
    std::cout << nums.size() << std::endl;
    std::cout << nums.capacity() << std::endl;
    std::cout << nums.max_size() << std::endl;

    auto& item1 = nums.front();
    item1 = -1;
    std::for_each(nums.cbegin(), nums.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;

    auto item2 = nums.front();
    item2 = 1;
    std::for_each(nums.cbegin(), nums.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;

    // front()可以返回可读，也可以返回可写
    // back()同理

    nums.push_back(10);
    std::for_each(nums.cbegin(), nums.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;

    nums.pop_back();
    std::for_each(nums.cbegin(), nums.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;

    nums.insert(nums.begin(), 0); // 在it前插入元素
    std::for_each(nums.cbegin(), nums.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;

    nums.emplace(nums.begin(), -2); // 插入对象不是类时，退化为insert()
    std::for_each(nums.cbegin(), nums.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;

    nums.emplace_back(0); // 插入对象不是类时，退化为push_back()
    std::for_each(nums.cbegin(), nums.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;

    std::cout << "---------------------------" << std::endl;

    std::cout << nums.size() << std::endl;
    std::cout << nums.capacity() << std::endl;
    std::cout << nums.max_size() << std::endl;

    std::cout << "---------------------------" << std::endl;

    nums.clear();
    std::cout << nums.size() << std::endl;
    std::cout << nums.capacity() << std::endl;
    std::cout << nums.max_size() << std::endl;

    std::cout << "---------------------------" << std::endl;

    nums.shrink_to_fit();
    std::cout << nums.size() << std::endl;
    std::cout << nums.capacity() << std::endl;
    std::cout << nums.max_size() << std::endl;

    std::vector<int>().swap(nums); // 此处的效果和shrink_to_fit()相同，释放内存

    nums.push_back(1);
    std::cout << nums.size() << std::endl;
    std::cout << nums.capacity() << std::endl;
    std::cout << nums.max_size() << std::endl;

    nums.insert(nums.begin(), -1);
    std::for_each(nums.cbegin(), nums.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;

    return 0;
}