#include <iostream>
#include <vector>

#if 0
// 非递归 闭区间版本[]
int binary_search(std::vector<int>& nums, int target)
{
    int left {};
    int right = nums.size() - 1;
    while (left <= right) {
        int middle = left + (right - left) / 2; // 防止int溢出
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
int binary_search(std::vector<int>& nums, int target)
{
    int left {};
    int right = nums.size();
    while (left < right) {
        int middle = left + (right - left) / 2; // 防止int溢出
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
int binary_search(std::vector<int>& nums, int target, int left, int right)
{
    if (left <= right) {
        int middle = left + (right - left) / 2; // 防止int溢出
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
int binary_search(std::vector<int>& nums, int target, int left, int right)
{
    if (left < right) {
        int middle = left + (right - left) / 2; // 防止int溢出
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
    std::vector<int> vi { -1, 0, 3, 5, 9, 12 };
    // std::cout << binary_search(vi, target) << std::endl;
    std::cout << binary_search(vi, target, 0, vi.size() - 1) << std::endl;
    // std::cout << binary_search(vi, target, 0, vi.size()) << std::endl;

    return 0;
}