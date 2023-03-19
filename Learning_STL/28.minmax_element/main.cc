#include <algorithm>
#include <iostream>
#include <list>

auto main(int argc, char* argv[]) -> int
{
    std::list nums { 1, 3, 6, 0, 0, 5, 3, 2, 1, 5, 6 };
    auto it_min = std::min_element(nums.begin(), nums.end());
    auto it_max = std::max_element(nums.begin(), nums.end());
    auto pair_minmax = std::minmax_element(nums.begin(), nums.end());

    std::cout << "min: " << *it_min << " position: " << std::distance(nums.begin(), it_min) << std::endl;
    std::cout << "max: " << *it_max << " position: " << std::distance(nums.begin(), it_max) << std::endl;
    // std::cout << std::distance(it_min, it_max) << std::endl;
    // std::cout << it_min - it_max << std::endl;
    // 1、distance()不取绝对值
    // 2、distance()对前大后小的数据，取值不确定
    std::cout << "distance: " << std::distance(nums.begin(), it_max) - std::distance(nums.begin(), it_min) << std::endl;

    std::cout << "min: " << *(pair_minmax.first) << " position: " << std::distance(nums.begin(), pair_minmax.first) << " max: " << *(pair_minmax.second) << " position: " << std::distance(nums.begin(), pair_minmax.second) << std::endl;
    std::cout << "distance: " << std::distance(nums.begin(), pair_minmax.second) - std::distance(nums.begin(), pair_minmax.first) << std::endl;

    // min_element()从左往右第一个最小的
    // max_element()从左往右第一个最大的
    // minmax_element()从左往右第一个最小的，从右往左第一个最大的

    return 0;
}