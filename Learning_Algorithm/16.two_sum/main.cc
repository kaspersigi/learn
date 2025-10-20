#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

std::vector<size_t> two_sum(std::vector<int>& nums, int target)
{
    std::vector<size_t> answer {};
    std::unordered_map<int, size_t> mi {};
    for (size_t i = 0; i < nums.size(); ++i) {
        auto it = mi.find(target - nums[i]);
        if (mi.find(target - nums[i]) != mi.end()) {
            answer.push_back(it->second);
            answer.push_back(i);
            break;
        } else
            mi.insert(std::pair<int, size_t>(nums[i], i));
    }
    return answer;
}

auto main(int argc, char* argv[]) -> int
{
    std::vector<int> vi { 2, 7, 11, 15 };
    int target { 9 };
    auto answer = two_sum(vi, target);
    std::for_each(answer.cbegin(), answer.cend(), [](auto e) { std::cout << e << " "; });
    std::cout << std::endl;
    return 0;
}