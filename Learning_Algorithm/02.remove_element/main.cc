#include <iostream>
#include <vector>

#if 0
移除元素
给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素，并返回移除后数组的新长度。
不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并原地修改输入数组。
元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。
示例 1: 给定 nums = [3,2,2,3], val = 3, 函数应该返回新的长度 2, 并且 nums 中的前两个元素均为 2。 你不需要考虑数组中超出新长度后面的元素。
示例 2: 给定 nums = [0,1,2,2,3,0,4,2], val = 2, 函数应该返回新的长度 5, 并且 nums 中的前五个元素为 0, 1, 3, 0, 4。
#endif

#if 0
// 暴力破解，双循环，O(n^2)
int remove_element(std::vector<int>& nums, int val)
{
    int length = nums.size();
    for (int i = 0; i < length; ++i) {
        if (nums[i] == val) {
            for (int j = i; j < length - 1; ++j)
                nums[j] = nums[j + 1];
            length--;
            i--; // 数组整体移动后，i--
        }
    }
    return length;
}
#endif

#if 1
// 快慢指针，O(n)
int remove_element(std::vector<int>& nums, int val)
{
    int slow = 0;
    for (size_t fast = 0; fast < nums.size(); ++fast) {
        if (nums[fast] != val) {
            nums[slow] = nums[fast];
            slow++;
        }
    }
    return slow;
}
#endif

auto main(int argc, char* argv[]) -> int
{
    int value = 2;
    std::vector<int> vi {
        0,
        1,
        2,
        2,
        3,
        0,
        4,
        2,
    };
    std::cout << remove_element(vi, value) << std::endl;

    return 0;
}