#include <algorithm>
#include <array>
#include <iostream>

template <typename T>
int change_array(T&& array)
{
    std::for_each(array.begin(), array.end(), [](auto& e) { e = e * 2; });
    return 0;
}

auto main(int argc, char* argv[]) -> int
{
    std::array nums { 1, 0, 2, 3, 0, 4, 5, 6, 0, 7, 8, 9 };
    std::cout << nums.size() << std::endl;
    std::cout << nums.max_size() << std::endl;
    std::for_each(nums.cbegin(), nums.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;
    change_array(nums);
    std::remove(nums.begin(), nums.end(), 0);
    std::for_each(nums.cbegin(), nums.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;
    // nums.earas(); //array没有erase函数

    return 0;
}