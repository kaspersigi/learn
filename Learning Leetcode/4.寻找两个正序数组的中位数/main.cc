#include <iostream>
#include <vector>

#define __MY_ANSWER__
//官方思路 找到两个数组的第k小的数

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
    {
#ifdef __MY_ANSWER__
        vector<int> nums(nums1.size() + nums2.size());
        size_t i = 0, j = 0, k = 0;
        while (i < nums1.size() && j < nums2.size()) {
            if (nums1[i] <= nums2[j]) {
                nums[k] = nums1[i];
                i++;
            } else {
                nums[k] = nums2[j];
                j++;
            }
            k++;
        }
        while (i < nums1.size()) {
            nums[k] = nums1[i];
            i++;
            k++;
        }
        while (j < nums2.size()) {
            nums[k] = nums2[j];
            j++;
            k++;
        }
        return nums.size() % 2 == 0 ? (nums[nums.size() / 2 - 1] + nums[nums.size() / 2]) / 2.0 : nums[nums.size() / 2];
#endif
    }
};

auto main(int argc, char* argv[]) -> int
{
    Solution s;
    vector<int> v1 { 1, 2 };
    vector<int> v2 { 3, 4 };
    auto result = s.findMedianSortedArrays(v1, v2);
    cout << result << endl;
    return 0;
}