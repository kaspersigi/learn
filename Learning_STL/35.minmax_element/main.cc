#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> words = { "apple", "dog", "elephant", "cat" };

    // 找字典序最小的单词
    auto min_it = std::min_element(words.begin(), words.end());
    std::cout << "Min word: " << *min_it << "\n"; // apple

    // 自定义比较：按长度找最长单词
    auto max_it = std::max_element(words.begin(), words.end(), [](const std::string& a, const std::string& b) {
        return a.length() < b.length(); // 按长度比较
    });
    std::cout << "Longest word: " << *max_it << "\n"; // elephant

    // ✅ 学习点：返回迭代器，可自定义比较谓词
}