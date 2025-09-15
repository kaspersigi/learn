#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> haystack = { 1, 2, 3, 4, 5, 6, 7, 8 };
    std::vector<int> needle = { 3, 4, 5 };

    auto it = std::search(haystack.begin(), haystack.end(),
        needle.begin(), needle.end());

    if (it != haystack.end()) {
        std::cout << "Found subsequence starting at index: "
                  << std::distance(haystack.begin(), it) << "\n"; // 2
    }

    // ✅ 学习点：通用子序列匹配，可用于任何容器
}