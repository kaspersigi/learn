#include <algorithm>
#include <iostream>
#include <vector>

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
#endif

auto main(int argc, char* argv[]) -> int
{
    std::vector<int> vi { -4, -1, 0, 3, 10 };
    auto v = sorted_squares(vi);
    std::for_each(v.cbegin(), v.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;

    return 0;
}