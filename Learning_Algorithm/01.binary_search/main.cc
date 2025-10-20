#include <iostream>
#include <vector>

#if 0
二分查找
给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target，写一个函数搜索 nums 中的 target，如果目标值存在返回下标，否则返回 -1。
eg1:
输入: nums = [-1,0,3,5,9,12], target = 9
输出: 4
解释: 9 出现在 nums 中并且下标为 4
eg2:
输入: nums = [-1,0,3,5,9,12], target = 2
输出: -1
解释: 2 不存在 nums 中因此返回 -1
提示：
1、你可以假设 nums 中的所有元素是不重复的。
2、n 将在 [1, 10000]之间。
3、nums 的每个元素都将在 [-9999, 9999]之间。
#endif

#if 0
// 非递归 闭区间版本[]
size_t binary_search(std::vector<int>& nums, int target)
{
    size_t left {};
    size_t right = nums.size() - 1;
    while (left <= right) {
        size_t middle = left + (right - left) / 2; // 防止int溢出
        if (target < nums[middle])
            right = middle - 1;
        else if (target > nums[middle])
            left = middle + 1;
        else
            return middle;
    }
    return -1;
}
#endif

#if 0
// 非递归 左闭右开版本[)
size_t binary_search(std::vector<int>& nums, int target)
{
    size_t left {};
    size_t right = nums.size();
    while (left < right) {
        size_t middle = left + (right - left) / 2; // 防止int溢出
        if (target < nums[middle])
            right = middle;
        else if (target > nums[middle])
            left = middle + 1;
        else
            return middle;
    }
    return -1;
}
#endif

#if 1
// 递归 闭区间版本[]
size_t binary_search(std::vector<int>& nums, int target, size_t left, size_t right)
{
    if (left <= right) {
        size_t middle = left + (right - left) / 2; // 防止int溢出
        if (target < nums[middle])
            return binary_search(nums, target, left, middle - 1);
        else if (target > nums[middle])
            return binary_search(nums, target, middle + 1, right);
        else
            return middle;
    }
    return -1;
}
#endif

#if 0
// 递归 左闭右开版本[)
size_t binary_search(std::vector<int>& nums, int target, size_t left, size_t right)
{
    if (left < right) {
        size_t middle = left + (right - left) / 2; // 防止int溢出
        if (target < nums[middle])
            return binary_search(nums, target, left, middle);
        else if (target > nums[middle])
            return binary_search(nums, target, middle + 1, right);
        else
            return middle;
    }
    return -1;
}
#endif

auto main(int argc, char* argv[]) -> int
{
    int target = 9;
    std::vector<int> vi {
        -1,
        0,
        3,
        5,
        9,
        12,
    };
    // std::cout << binary_search(vi, target) << std::endl;
    std::cout << binary_search(vi, target, 0, vi.size() - 1) << std::endl;
    // std::cout << binary_search(vi, target, 0, vi.size()) << std::endl;

    return 0;
}