#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<std::string> words = { "apple", "cat", "banana", "dog" };

    // 找第一个长度 > 3 的单词
    auto it = std::find_if(words.begin(), words.end(), [](const std::string& s) {
        return s.length() > 3;
    });

    if (it != words.end()) {
        std::cout << "First long word: " << *it << "\n"; // 输出: apple
    }

    // ✅ 学习点：条件查找，灵活强大
    // ✅ 可组合复杂逻辑（如：找第一个偶数且大于10）
}