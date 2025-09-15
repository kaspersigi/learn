#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v = { 10, 20, 30, 40, 50 };

    auto it = std::find(v.begin(), v.end(), 30);

    if (it != v.end()) {
        std::cout << "Found 30 at index: " << std::distance(v.begin(), it) << "\n"; // 输出: 2
    } else {
        std::cout << "Not found\n";
    }

    // ✅ 学习点：返回迭代器，没找到返回 end()
}