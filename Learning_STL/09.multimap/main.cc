// ============================
// file: learn_std_multimap.cc
// 说明：全面学习 std::multimap 的现代 C++ 用法
// 编译：g++ -std=c++17 learn_std_multimap.cc -o learn_multimap
// ============================

#include <algorithm> // for_each, transform
#include <functional> // std::greater
#include <iterator> // std::inserter
#include <map> // multimap 在 <map> 头文件中
#include <numeric>
#include <print> // C++23
#include <string>

// 辅助函数：打印 multimap
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
struct Course {
    std::string name;
    Course(std::string n)
        : name(std::move(n))
    {
    }
    bool operator<(const Course& other) const { return name < other.name; }
};

// 自定义值类型
struct GradeRecord {
    std::string student;
    int score;
    GradeRecord(std::string s, int sc)
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
    std::multimap<std::string, std::string> phonebook;
    phonebook.insert({ "Alice", "123-4567" });
    phonebook.insert({ "Bob", "234-5678" });
    phonebook.insert({ "Alice", "345-6789" }); // 同一个键，允许！
    phonebook.insert({ "Charlie", "456-7890" });
    phonebook.insert({ "Alice", "567-8901" }); // 再次插入 Alice

    print_multimap(phonebook, "phonebook (允许重复键)");

    // ✅ 初始化列表（重复键全部保留）
    std::multimap<int, std::string> scores {
        { 85, "Bob" },
        { 90, "Alice" },
        { 85, "Charlie" }, // 同分！允许
        { 95, "Diana" },
        { 90, "Eve" } // 同分！允许
    };
    print_multimap(scores, "scores (初始化列表)");

    // ✅ 使用自定义比较器（降序）
    std::multimap<int, std::string, std::greater<int>> desc_scores {
        { 85, "Bob" },
        { 90, "Alice" },
        { 85, "Charlie" },
        { 95, "Diana" }
    };
    print_multimap(desc_scores, "desc_scores (按键降序)");

    // ✅ 拷贝构造
    std::multimap<std::string, std::string> copy_phonebook = phonebook;
    print_multimap(copy_phonebook, "copy_phonebook");
}

// 示例 2: 插入与访问（注意：无 operator[]！）
void example_insert_access()
{
    std::println("\n=== 示例 2: 插入与访问 ===");

    std::multimap<std::string, int> student_scores;

    // ✅ insert —— 总是成功（无 bool 返回值）
    student_scores.insert({ "Alice", 95 });
    student_scores.insert({ "Bob", 87 });
    student_scores.insert({ "Alice", 92 }); // 允许重复键
    student_scores.insert({ "Charlie", 90 });
    student_scores.insert({ "Alice", 88 }); // 再次插入 Alice

    // ✅ emplace —— 原地构造
    student_scores.emplace("Bob", 89); // Bob 有第二个成绩

    print_multimap(student_scores, "student_scores");

    // ❌ multimap 没有 operator[]！
    // student_scores["Alice"] = 100; // 编译错误！

    // ✅ 访问：必须用 find / equal_range
    auto it = student_scores.find("Alice");
    if (it != student_scores.end()) {
        std::println("find('Alice') 找到第一个: {}分", it->second);
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

    std::multimap<std::string, int> m {
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

    // ✅ erase by range
    auto start = m.lower_bound("B"); // 第一个 >= "B"
    auto end = m.upper_bound("C"); // 第一个 > "C"
    m.erase(start, end); // 删除 [B, C] 范围内所有键
    print_multimap(m, "范围删除 [B,C) 后");

    // ✅ clear
    m.clear();
    std::println("clear 后 size = {}", m.size());
}

// 示例 4: 范围查询与遍历
void example_range_iterate()
{
    std::println("\n=== 示例 4: 范围查询与遍历 ===");

    std::multimap<int, std::string> m {
        { 85, "Bob" },
        { 90, "Alice" },
        { 85, "Charlie" },
        { 95, "Diana" },
        { 90, "Eve" },
        { 88, "Frank" }
    };

    print_multimap(m, "成绩表");

    // ✅ lower_bound —— 第一个 >= key
    auto lb = m.lower_bound(90);
    std::println("lower_bound(90): {} -> {}", lb->first, lb->second);

    // ✅ upper_bound —— 第一个 > key
    auto ub = m.upper_bound(90);
    std::println("upper_bound(90): {} -> {}", ub->first, ub->second);

    // ✅ equal_range —— 获取某个键的所有元素
    auto [first, last] = m.equal_range(90);
    std::println("equal_range(90): 所有90分的学生:");
    for (auto it = first; it != last; ++it) {
        std::println("  {}", it->second);
    }

    // ✅ 范围遍历：打印所有分数 >=88 且 <95 的学生
    std::println("分数在 [88, 95) 的学生:");
    auto range_start = m.lower_bound(88);
    auto range_end = m.lower_bound(95);
    for (auto it = range_start; it != range_end; ++it) {
        std::println("  {}: {}分", it->second, it->first);
    }

    // ✅ 正向遍历
    std::println("正向遍历 (升序):");
    for (const auto& [score, name] : m) {
        std::println("  {}: {}分", name, score);
    }

    // ✅ 反向遍历
    std::println("反向遍历 (降序):");
    for (auto it = m.rbegin(); it != m.rend(); ++it) {
        std::println("  {}: {}分", it->second, it->first);
    }
}

// 示例 5: 自定义键类型（允许“相等”键）
void example_custom_key()
{
    std::println("\n=== 示例 5: 自定义键类型 ===");

    std::multimap<Course, GradeRecord> grade_db;
    grade_db.emplace(Course("Math"), GradeRecord("Alice", 95));
    grade_db.emplace(Course("English"), GradeRecord("Bob", 87));
    grade_db.emplace(Course("Math"), GradeRecord("Charlie", 92)); // 同一门课
    grade_db.emplace(Course("Science"), GradeRecord("Diana", 90));
    grade_db.emplace(Course("Math"), GradeRecord("Eve", 88)); // 同一门课

    std::println("成绩数据库 (按课程排序，允许同课程多学生):");
    for (const auto& [course, record] : grade_db) {
        std::println("  {}: {} ({}分)", course.name, record.student, record.score);
    }

    // ✅ 查找某门课程的所有成绩
    auto [first, last] = grade_db.equal_range(Course("Math"));
    std::println("Math 课程的所有成绩:");
    for (auto it = first; it != last; ++it) {
        std::println("  {}: {}分", it->second.student, it->second.score);
    }
}

// 示例 6: 与 STL 算法配合
void example_algorithms()
{
    std::println("\n=== 示例 6: 与 STL 算法配合 ===");

    std::multimap<std::string, int> m {
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
    std::multimap<std::string, std::string> desc_map;
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

// 示例 7: 性能与使用建议
void example_performance()
{
    std::println("\n=== 示例 7: 性能与使用建议 ===");

    std::println("std::multimap 特性总结:");
    std::println("  - 底层: 红黑树（同 map）");
    std::println("  - 插入/删除/查找: O(log n)");
    std::println("  - 自动排序: 按键排序");
    std::println("  - 允许重复键: 同一键可多次插入");
    std::println("  - 迭代器稳定: 插入/删除不影响其他迭代器");

    std::println("\n何时使用 multimap:");
    std::println("  - 需要维护一对多的映射关系");
    std::println("  - 频繁插入/删除/查找，且需保持有序");
    std::println("  - 需要按键范围查询（如‘所有数学课成绩’）");

    std::println("\n何时不使用 multimap:");
    std::println("  - 不需要排序 → 用 unordered_multimap（哈希表）");
    std::println("  - 数据量小 → 用 vector<pair> + 排序，可能更快");
    std::println("  - 只需统计每个键的总和 → 用 map<key, sum>");

    std::println("\n与 map 的关键区别:");
    std::println("  - map::insert 返回 pair<iterator, bool>");
    std::println("  - multimap::insert 返回 iterator（总是成功）");
    std::println("  - map 有 operator[]，multimap 没有！");
    std::println("  - map::erase(key) 返回 0 或 1");
    std::println("  - multimap::erase(key) 返回删除的元素个数（可能>1）");
    std::println("  - map::count(key) 返回 0 或 1");
    std::println("  - multimap::count(key) 返回出现次数（可能>1）");
}

// 主函数
auto main(int argc, char* argv[]) -> int
{
    example_basic();
    example_insert_access();
    example_erase();
    example_range_iterate();
    example_custom_key();
    example_algorithms();
    example_performance();

    std::println("\n✅ std::multimap 学习完成！");
    return 0;
}