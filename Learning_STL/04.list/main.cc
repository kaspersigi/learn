#include <algorithm>
#include <iostream>
#include <list>

auto main(int argc, char* argv[]) -> int
{
    std::list nums { 1, 0, 2, 3, 0, 4, 5, 6, 0, 7, 8, 9 };
    std::cout << nums.size() << std::endl;
    std::cout << nums.max_size() << std::endl;

    std::for_each(nums.cbegin(), nums.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;

    nums.remove(0);
    std::for_each(nums.cbegin(), nums.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;
    std::cout << nums.size() << std::endl;
    std::cout << nums.max_size() << std::endl;

    std::list nums2 { 1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5 };
    std::for_each(nums2.cbegin(), nums2.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;
    std::cout << nums2.size() << std::endl;
    std::cout << nums2.max_size() << std::endl;

    nums2.unique();
    // nums2.unique([](auto e, auto f) { return e == f; });//本意是对对象进行unique，自己动手写谓词
    std::for_each(nums2.cbegin(), nums2.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;
    std::cout << nums2.size() << std::endl;
    std::cout << nums2.max_size() << std::endl;

    nums.reverse();
    std::for_each(nums.cbegin(), nums.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;
    std::cout << nums.size() << std::endl;
    std::cout << nums.max_size() << std::endl;

    nums.sort();
    std::for_each(nums.cbegin(), nums.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;
    std::cout << nums.size() << std::endl;
    std::cout << nums.max_size() << std::endl;

    decltype(nums) nums3;
    nums3.splice(nums3.end(), nums, nums.begin()); // 将nums的元素移到nums3中
    std::for_each(nums3.cbegin(), nums3.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;
    std::cout << nums3.size() << std::endl;
    std::cout << nums3.max_size() << std::endl;

    std::for_each(nums.cbegin(), nums.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;
    std::cout << nums.size() << std::endl;
    std::cout << nums.max_size() << std::endl;

    std::list nums4 { 1, 3, 5, 7, 9 };
    std::list nums5 { 2, 4, 6, 8, 10 };
    nums4.merge(nums5); // 两个有序list，将nums5移动到nums4中
    std::for_each(nums4.cbegin(), nums4.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;
    std::for_each(nums5.cbegin(), nums5.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;

    nums4.swap(nums5);
    std::for_each(nums4.cbegin(), nums4.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;
    std::for_each(nums5.cbegin(), nums5.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;

    for (auto i = nums.begin(); i != nums.end(); ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;

    decltype(nums) nums6;
    nums6.push_back(1);
    nums6.push_back(2);
    nums6.push_back(3);
    nums6.push_back(4);
    nums6.push_back(5);
    nums6.push_back(6);
    nums6.push_back(7);
    nums6.push_back(8);
    std::for_each(nums6.cbegin(), nums6.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;
    // 对list，push_front()头插，push_back()尾插

    return 0;
}