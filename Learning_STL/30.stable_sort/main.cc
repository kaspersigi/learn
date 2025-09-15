#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Student {
    std::string name;
    int score;
};

int main()
{
    std::vector<Student> students = {
        { "Alice", 85 },
        { "Bob", 90 },
        { "Charlie", 85 }, // 和 Alice 同分
        { "David", 95 }
    };

    // 按分数排序，同分者保持输入顺序（稳定）
    std::stable_sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.score > b.score; // 分数降序
    });

    std::cout << "Stable sorted by score:\n";
    for (const auto& s : students) {
        std::cout << s.name << ": " << s.score << "\n";
    }
    // 输出：
    // David: 95
    // Bob: 90
    // Alice: 85   ← 同分，Alice 在 Charlie 前（输入顺序保留）
    // Charlie: 85

    // ✅ 学习点：当排序依据不唯一时，保持“原有相对顺序”
}