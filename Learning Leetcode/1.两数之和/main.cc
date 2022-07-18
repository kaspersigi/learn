#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

// #define __MY_ANSWER__
// #define __ANSWER_CIRCLE__
#define __ANSWER_HASHTABLE__

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target)
    {
#ifdef __MY_ANSWER__
        vector<int> result;
        auto n = find_if(nums.cbegin(), nums.cend(), [=, &result](auto e) {
            auto m = find_if(nums.crbegin(), nums.crend(), [=, &result](auto f) { return (target == e + f); });
            if (m != nums.crend()) {
                result.push_back(nums.crbegin() - m + nums.size() - 1);
                return true;
            } else
                return false;
        });
        result.push_back(n - nums.cbegin());
        return result;
#endif

#ifdef __ANSWER_CIRCLE__
        auto n = nums.size();
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = i + 1; j < n; ++j) {
                if (nums[i] + nums[j] == target) {
                    return { static_cast<int>(i), static_cast<int>(j) };
                }
            }
        }
        return {};
#endif

#ifdef __ANSWER_HASHTABLE__
        unordered_map<int, int> hashtable;
        for (size_t i = 0; i < nums.size(); ++i) {
            auto it = hashtable.find(target - nums[i]);
            if (it != hashtable.end()) {
                return { it->second, static_cast<int>(i) };
            }
            hashtable[nums[i]] = i;
        }
        return {};
#endif
    }
};

auto main(int argc, char* argv[]) -> int
{
    Solution s;
    vector<int> nums { 3, 3 };
    auto result = s.twoSum(nums, 6);
    for_each(result.cbegin(), result.cend(), [](auto e) { cout << e << " "; });

    return 0;
}