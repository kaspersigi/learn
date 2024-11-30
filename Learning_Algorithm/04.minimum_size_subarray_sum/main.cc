#include <cstdint>
#include <iostream>
#include <vector>

#if 0
长度最小的子数组
给定一个含有 n 个正整数的数组和一个正整数 s ，找出该数组中满足其和 ≥ s 的长度最小的连续子数组，并返回其长度。如果不存在符合条件的子数组，返回 0。
示例：
输入：s = 7, nums = [2,3,1,2,4,3]
输出：2
解释：子数组 [4,3] 是该条件下的长度最小的子数组。
提示：
1 <= target <= 10^9
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^5
#endif

#if 0
// 暴力破解法，O(n^2)
int min_sub_array_len(int target, std::vector<int>& nums)
{
    int answer { INT32_MAX };
    for (size_t i = 0; i < nums.size(); ++i) {
        int sum {};
        int length {};
        for (size_t j = i; j < nums.size(); ++j) {
            if (sum + nums[j] < target) {
                sum += nums[j];
            } else {
                length = j - i + 1;
                if (length < answer)
                    answer = length;
                break;
            }
        }
    }
    return INT32_MAX == answer ? 0 : answer;
}
#endif

#if 0
// 滑动窗口，O(n)
int min_sub_array_len(int target, std::vector<int>& nums)
{
    int slow {};
    int fast {};
    int sum {};
    int answer { INT32_MAX };
    while (fast < nums.size()) { // 到底是遍历起点，还是终点
        sum += nums[fast];
        while (sum >= target) {
            answer = fast - slow + 1 < answer ? fast - slow + 1 : answer;
            sum -= nums[slow++];
        }
        fast++;
    }
    return INT32_MAX == answer ? 0 : answer;
}
#else
int min_sub_array_len(int target, std::vector<int>& nums)
{
    int answer { 0 };
    return answer;
}
#endif

auto main(int argc, char* argv[]) -> int
{
    int target = 7;
    std::vector<int> vi {
        2,
        3,
        1,
        2,
        4,
        3,
    };
    std::cout << min_sub_array_len(target, vi) << std::endl;
    return 0;
}