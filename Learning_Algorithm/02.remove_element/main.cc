#include <iostream>
#include <vector>

#if 0
// 暴力破解，双循环，O(n^2)
int remove_element(std::vector<int>& nums, int value)
{
    int length = nums.size();
    for (int i = 0; i < length; ++i) {
        if (nums[i] == value) {
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
int remove_element(std::vector<int>& nums, int value)
{
    int slow = 0;
    for (size_t fast = 0; fast < nums.size(); ++fast) {
        if (nums[fast] != value) {
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
    std::vector<int> vi { 0, 1, 2, 2, 3, 0, 4, 2 };
    std::cout << remove_element(vi, value) << std::endl;

    return 0;
}