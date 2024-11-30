#include <algorithm>
#include <iostream>
#include <vector>

#if 0
有序数组的平方
给你一个按 非递减顺序 排序的整数数组 nums，返回 每个数字的平方 组成的新数组，要求也按 非递减顺序 排序。
示例 1：
输入：nums = [-4,-1,0,3,10]
输出：[0,1,9,16,100]
解释：平方后，数组变为 [16,1,0,9,100]，排序后，数组变为 [0,1,9,16,100]
示例 2：
输入：nums = [-7,-3,2,3,11]
输出：[4,9,9,49,121]
#endif

#if 0
// 暴力破解，双循环，O(n+nlogn)
std::vector<int> sorted_squares(std::vector<int>& nums)
{
    std::vector<int> vi {};
    std::for_each(nums.cbegin(), nums.cend(), [&](auto e) { vi.push_back(e * e); });
    std::sort(vi.begin(), vi.end());
    return vi;
}
#endif

#if 1
// 快慢指针，单循环，O(n)
std::vector<int> sorted_squares(std::vector<int>& nums)
{
    std::vector<int> vi(nums.size(), 0);
    size_t slow {};
    size_t fast { nums.size() - 1 };
    size_t pos { nums.size() - 1 };
    while (slow <= fast) {
        if (nums[fast] * nums[fast] > nums[slow] * nums[slow]) {
            vi[pos] = nums[fast] * nums[fast];
            --fast;
        } else {
            vi[pos] = nums[slow] * nums[slow];
            ++slow;
        }
        pos--;
    }
    return vi;
}
#else
std::vector<int> sorted_squares(std::vector<int>& vi)
{
    size_t slow { 0 };
    size_t fast = { vi.size() - 1 };
    size_t pos = { vi.size() - 1 };
    std::vector<int> vo(vi.size(), 0);
    while (slow < fast) {
        if (vi[slow] * vi[slow] > vi[fast] * vi[fast]) {
            vo[pos] = vi[slow] * vi[slow];
            pos--;
            slow++;
        } else {
            vo[pos] = vi[fast] * vi[fast];
            pos--;
            fast--;
        }
    }
    return vo;
}
#endif

auto main(int argc, char* argv[]) -> int
{
    std::vector<int> vi { -4, -1, 0, 3, 10 };
    auto v = sorted_squares(vi);
    std::for_each(v.cbegin(), v.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;

    return 0;
}