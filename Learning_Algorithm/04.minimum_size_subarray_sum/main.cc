#include <cstdint>
#include <iostream>
#include <vector>

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

#if 1
// 滑动窗口
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
#endif

auto main(int argc, char* argv[]) -> int
{
    int target = 7;
    std::vector<int> vi { 2, 3, 1, 2, 4, 3 };
    std::cout << min_sub_array_len(target, vi) << std::endl;
    return 0;
}