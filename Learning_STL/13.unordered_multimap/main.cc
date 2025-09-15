// ============================
// file: learn_std_unordered_multimap.cc
// 说明：全面学习 std::unordered_multimap 的现代 C++ 用法
// 编译：g++ -std=c++17 learn_std_unordered_multimap.cc -o learn_unordered_multimap
// ============================

#include <algorithm> // for_each, transform
#include <functional> // std::hash, std::equal_to
#include <iterator> // std::inserter
#include <numeric>
#include <print> // C++23
#include <string>
#include <unordered_map> // unordered_multimap 在 <unordered_map> 中

// 辅助函数：打印 multimap（无序，顺序不确定）
template <typename Map>
void print_multimap(const Map& m, const char* label = "")
{
    if (*label)
        std::println("{}:", label);
    for (const auto& [key, value] : m) {
        std::println("  {}: {}", key, value);
    }
    std::println("");
}

// 自定义键类型
struct CourseName {
    std::string name;
    CourseName(std::string n)
        : name(std::move(n))
    {
    }
    bool operator==(const CourseName& other) const { return name == other.name; }
};

// 为 CourseName 提供哈希函数
namespace std {
template <>
struct hash<CourseName> {
    size_t operator()(const CourseName& c) const
    {
        return hash<string>()(c.name);
    }
};
}

// 自定义值类型
struct StudentRecord {
    std::string student;
    int score;
    StudentRecord(std::string s, int sc)
        : student(std::move(s))
        , score(sc)
    {
    }
};

// 示例 1: 基本用法与初始化（允许重复键！）
void example_basic()
{
    std::println("\n=== 示例 1: 基本用法与初始化（允许重复键） ===");

    // ✅ 默认构造
    std::unordered_multimap<std::string, std::string> phonebook;
    phonebook.insert({ "Alice", "123-4567" });
    phonebook.insert({ "Bob", "234-5678" });
    phonebook.insert({ "Alice", "345-6789" }); // 同一个键，允许！
    phonebook.insert({ "Charlie", "456-7890" });
    phonebook.insert({ "Alice", "567-8901" }); // 再次插入 Alice

    print_multimap(phonebook, "phonebook (允许重复键)");

    // ✅ 初始化列表（重复键全部保留）
    std::unordered_multimap<int, std::string> scores {
        { 85, "Bob" },
        { 90, "Alice" },
        { 85, "Charlie" }, // 同分！允许
        { 95, "Diana" },
        { 90, "Eve" } // 同分！允许
    };
    print_multimap(scores, "scores (初始化列表)");

    // ✅ 使用自定义哈希
    std::unordered_multimap<CourseName, StudentRecord> grade_db;
    grade_db.emplace(CourseName("Math"), StudentRecord("Alice", 95));
    grade_db.emplace(CourseName("English"), StudentRecord("Bob", 87));
    grade_db.emplace(CourseName("Math"), StudentRecord("Charlie", 92)); // 同一门课
    grade_db.emplace(CourseName("Science"), StudentRecord("Diana", 90));

    std::println("grade_db (自定义键类型):");
    for (const auto& [course, record] : grade_db) {
        std::println("  {}: {} ({}分)", course.name, record.student, record.score);
    }

    // ✅ 指定桶数量
    std::unordered_multimap<std::string, int> bucket_map(15); // 预分配15个桶
    bucket_map.insert({ "a", 1 });
    bucket_map.insert({ "b", 2 });
    bucket_map.insert({ "a", 3 }); // 重复键
    print_multimap(bucket_map, "bucket_map (预分配15桶)");

    // ✅ 拷贝构造
    std::unordered_multimap<std::string, std::string> copy_phonebook = phonebook;
    print_multimap(copy_phonebook, "copy_phonebook");
}

// 示例 2: 插入与访问（注意：无 operator[]！）
void example_insert_access()
{
    std::println("\n=== 示例 2: 插入与访问 ===");

    std::unordered_multimap<std::string, int> student_scores;

    // ✅ insert —— 总是成功（无 bool 返回值）
    student_scores.insert({ "Alice", 95 });
    student_scores.insert({ "Bob", 87 });
    student_scores.insert({ "Alice", 92 }); // 允许重复键
    student_scores.insert({ "Charlie", 90 });
    student_scores.insert({ "Alice", 88 }); // 再次插入 Alice

    // ✅ emplace —— 原地构造
    student_scores.emplace("Bob", 89); // Bob 有第二个成绩

    print_multimap(student_scores, "student_scores");

    // ❌ unordered_multimap 没有 operator[]！
    // student_scores["Alice"] = 100; // 编译错误！

    // ✅ 访问：必须用 find / equal_range
    auto it = student_scores.find("Alice");
    if (it != student_scores.end()) {
        std::println("find('Alice') 找到一个: {}分", it->second);
    }

    // ✅ count —— 返回该键对应的元素个数
    std::println("Alice 的成绩个数: {}", student_scores.count("Alice"));

    // ✅ 遍历某个键的所有值 —— 使用 equal_range
    auto [first, last] = student_scores.equal_range("Alice");
    std::println("Alice 的所有成绩:");
    for (auto it = first; it != last; ++it) {
        std::println("  {}分", it->second);
    }
}

// 示例 3: 删除（注意：erase(key) 删除所有匹配键！）
void example_erase()
{
    std::println("\n=== 示例 3: 删除 ===");

    std::unordered_multimap<std::string, int> m {
        { "Alice", 95 },
        { "Bob", 87 },
        { "Alice", 92 },
        { "Charlie", 90 },
        { "Alice", 88 },
        { "Bob", 89 }
    };

    print_multimap(m, "原始");

    // ✅ erase by key —— 删除所有等于该键的元素！
    size_t erased = m.erase("Alice"); // 删除所有 Alice 的记录
    std::println("删除键 'Alice': 删除了 {} 个元素", erased);
    print_multimap(m, "删除所有 Alice 后");

    // ✅ erase by iterator —— 只删除一个元素
    auto it = m.find("Bob");
    if (it != m.end()) {
        m.erase(it); // 只删除第一个 Bob
    }
    print_multimap(m, "删除一个 Bob 后");

    // ✅ clear
    m.clear();
    std::println("clear 后 size = {}", m.size());
}

// 示例 4: 查找与范围查询
void example_find_range()
{
    std::println("\n=== 示例 4: 查找与范围查询 ===");

    std::unordered_multimap<int, std::string> m {
        { 85, "Bob" },
        { 90, "Alice" },
        { 85, "Charlie" },
        { 95, "Diana" },
        { 90, "Eve" },
        { 88, "Frank" }
    };

    print_multimap(m, "成绩表");

    // ✅ find —— 返回任意一个匹配的迭代器
    auto it = m.find(90);
    if (it != m.end()) {
        std::println("find(90) 找到一个: {} ({}分)", it->second, it->first);
    }

    // ✅ count —— 返回该键对应的元素个数
    std::println("90分的学生个数: {}", m.count(90));

    // ✅ equal_range —— 获取某个键的所有元素
    auto [first, last] = m.equal_range(85);
    std::println("85分的所有学生:");
    for (auto it = first; it != last; ++it) {
        std::println("  {}", it->second);
    }

// ✅ contains (C++20)
#if __cplusplus >= 202002L
    if (m.contains(95)) {
        std::println("包含95分的记录");
    }
#endif

    // ✅ 哈希表信息
    std::println("size: {}", m.size());
    std::println("bucket_count: {}", m.bucket_count());
    std::println("load_factor: {:.2f}", m.load_factor());
}

// 示例 5: 与 STL 算法配合
void example_algorithms()
{
    std::println("\n=== 示例 5: 与 STL 算法配合 ===");

    std::unordered_multimap<std::string, int> m {
        { "apple", 3 },
        { "banana", 5 },
        { "apple", 2 },
        { "cherry", 4 },
        { "banana", 3 }
    };

    // ✅ for_each —— 遍历并修改值
    std::for_each(m.begin(), m.end(), [](auto& pair) {
        pair.second += 10; // 每个数量+10
    });
    print_multimap(m, "每个数量+10后");

    // ✅ transform —— 创建新 multimap
    std::unordered_multimap<std::string, std::string> desc_map;
    std::transform(m.begin(), m.end(), std::inserter(desc_map, desc_map.begin()),
        [](const auto& pair) {
            return std::make_pair(pair.first, "count=" + std::to_string(pair.second));
        });
    print_multimap(desc_map, "描述性 multimap");

    // ✅ accumulate —— 计算总数量（注意：同一个键可能有多个值）
    int total = std::accumulate(m.begin(), m.end(), 0,
        [](int sum, const auto& pair) { return sum + pair.second; });
    std::println("总数量: {}", total);
}

// 示例 6: 性能与使用建议
void example_performance()
{
    std::println("\n=== 示例 6: 性能与使用建议 ===");

    std::println("std::unordered_multimap 特性总结:");
    std::println("  - 底层: 哈希表（同 unordered_map）");
    std::println("  - 插入/删除/查找: 平均 O(1)，最坏 O(n)");
    std::println("  - 无序: 遍历顺序不确定");
    std::println("  - 允许重复键: 同一键可多次插入");
    std::println("  - 迭代器稳定性: ❌ 插入可能导致 rehash，使所有迭代器失效！");

    std::println("\n何时使用 unordered_multimap:");
    std::println("  - 需要维护一对多的映射关系，且性能优先于排序");
    std::println("  - 频繁插入/删除/查找，数据量大（> 1000）");
    std::println("  - 如倒排索引、电话簿、日志聚合等场景");

    std::println("\n何时不使用 unordered_multimap:");
    std::println("  - 需要按键排序 → 用 multimap");
    std::println("  - 数据量小 → 用 vector<pair> + 排序，可能更快");
    std::println("  - 只需统计每个键的总和 → 用 unordered_map<key, sum>");

    std::println("\n与 unordered_map 的关键区别:");
    std::println("  - unordered_map::insert 返回 pair<iterator, bool>");
    std::println("  - unordered_multimap::insert 返回 iterator（总是成功）");
    std::println("  - unordered_map 有 operator[]，unordered_multimap 没有！");
    std::println("  - unordered_map::erase(key) 返回 0 或 1");
    std::println("  - unordered_multimap::erase(key) 返回删除的元素个数（可能>1）");
    std::println("  - unordered_map::count(key) 返回 0 或 1");
    std::println("  - unordered_multimap::count(key) 返回出现次数（可能>1）");
}

// 主函数
auto main(int argc, char* argv[]) -> int
{
    example_basic();
    example_insert_access();
    example_erase();
    example_find_range();
    example_algorithms();
    example_performance();

    std::println("\n✅ std::unordered_multimap 学习完成！");
    return 0;
}