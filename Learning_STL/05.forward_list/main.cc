#include <algorithm>
#include <forward_list>
#include <iostream>

auto main(int argc, char* argv[]) -> int
{
    std::forward_list nums {
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
    // forward_list构造是一个头插法的单链表
    // 但是初始化列表初始的顺序，就是访问的顺序
    // 相当于将初始化列表逆序头插

    std::for_each(nums.cbegin(), nums.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;

    for (auto i = nums.begin(); i != nums.end(); ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;

    decltype(nums) nums2;
    nums2.push_front(1);
    nums2.push_front(2);
    nums2.push_front(3);
    nums2.push_front(4);
    nums2.push_front(5);
    nums2.push_front(6);
    nums2.push_front(7);
    std::for_each(nums2.cbegin(), nums2.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;

    nums2.remove(1);
    std::for_each(nums2.cbegin(), nums2.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;

    auto it = nums2.before_begin();
    nums2.insert_after(it, 8); // vector、list中的insert()是在it前插入，forward_list中的insert_after()是在it之前插入
    std::for_each(nums2.cbegin(), nums2.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;

    return 0;
}