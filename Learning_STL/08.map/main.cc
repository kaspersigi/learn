// ============================
// file: learn_std_map.cc
// 说明：全面学习 std::map 的现代 C++ 用法
// 编译：g++ -std=c++17 learn_std_map.cc -o learn_map
// ============================

#include <algorithm> // transform, for_each
#include <functional> // std::greater
#include <iterator> // std::inserter
#include <map>
#include <numeric>
#include <print> // C++23
#include <string>

// 辅助函数：打印 map
template <typename Map>
void print_map(const Map& m, const char* label = "")
{
    if (*label)
        std::println("{}:", label);
    for (const auto& [key, value] : m) { // C++17 结构化绑定
        std::println("  {}: {}", key, value);
    }
    std::println("");
}

// 自定义键类型
struct StudentID {
    int id;
    StudentID(int i)
        : id(i)
    {
    }
    bool operator<(const StudentID& other) const { return id < other.id; } // 必须可比较
};

// 自定义值类型
struct StudentInfo {
    std::string name;
    int grade;
    StudentInfo(std::string n, int g)
        : name(std::move(n))
        , grade(g)
    {
    }
};

// 示例 1: 基本用法与初始化
void example_basic()
{
    std::println("\n=== 示例 1: 基本用法与初始化 ===");

    // ✅ 默认构造（按键升序）
    std::map<std::string, int> word_count;
    word_count["apple"] = 3;
    word_count["banana"] = 5;
    word_count["cherry"] = 2;
    word_count["apple"] = 4; // 重复键 → 覆盖旧值！

    print_map(word_count, "word_count (升序)");

    // ✅ 初始化列表
    std::map<int, std::string> id_to_name {
        { 101, "Alice" },
        { 103, "Bob" },
        { 102, "Charlie" },
        { 101, "David" } // 重复键 → David 会覆盖 Alice！
    };
    print_map(id_to_name, "id_to_name (初始化列表，重复键被覆盖)");

    // ✅ 使用自定义比较器（降序）
    std::map<int, std::string, std::greater<int>> desc_map {
        { 101, "Alice" },
        { 103, "Bob" },
        { 102, "Charlie" }
    };
    print_map(desc_map, "desc_map (按键降序)");

    // ✅ 拷贝构造
    std::map<std::string, int> copy_map = word_count;
    print_map(copy_map, "copy_map");
}

// 示例 2: 插入与访问（多种方式）
void example_insert_access()
{
    std::println("\n=== 示例 2: 插入与访问 ===");

    std::map<std::string, int> scores;

    // ✅ 方式1: operator[] —— 不存在则插入默认值（0），然后赋值
    scores["Alice"] = 95;
    scores["Bob"] = 87;
    scores["Alice"] = 98; // 存在则覆盖

    // ✅ 方式2: insert —— 返回 pair<iterator, bool>
    auto [it1, success1] = scores.insert({ "Charlie", 92 });
    std::println("插入 Charlie: {}", success1 ? "成功" : "失败（键已存在）");

    auto [it2, success2] = scores.insert({ "Bob", 88 }); // Bob 已存在 → 失败，不覆盖！
    std::println("插入 Bob: {}", success2 ? "成功" : "失败（键已存在）");
    std::println("Bob 的分数仍是: {}", it2->second);

    // ✅ 方式3: emplace —— 原地构造 pair
    auto [it3, success3] = scores.emplace("Diana", 90);
    std::println("emplace Diana: {}", success3 ? "成功" : "失败");

    // ✅ 方式4: try_emplace (C++17) —— 不存在才构造
    auto [it4, success4] = scores.try_emplace("Alice", 100); // Alice 存在 → 不构造，不覆盖
    std::println("try_emplace Alice: {}", success4 ? "成功" : "失败");
    std::println("Alice 的分数仍是: {}", it4->second);

    // ✅ 方式5: insert_or_assign (C++17) —— 存在则赋值，不存在则插入
    auto [it5, success5] = scores.insert_or_assign("Eve", 85); // Eve 不存在 → 插入
    auto [it6, success6] = scores.insert_or_assign("Bob", 89); // Bob 存在 → 赋值
    std::println("insert_or_assign Eve: {}", success5 ? "插入" : "赋值");
    std::println("insert_or_assign Bob: {}", success6 ? "插入" : "赋值");

    print_map(scores, "最终 scores");
}

// 示例 3: 查找与删除
void example_find_erase()
{
    std::println("\n=== 示例 3: 查找与删除 ===");

    std::map<std::string, int> m {
        { "Alice", 95 },
        { "Bob", 87 },
        { "Charlie", 92 },
        { "Diana", 90 }
    };

    print_map(m, "原始");

    // ✅ find —— 返回迭代器
    auto it = m.find("Bob");
    if (it != m.end()) {
        std::println("找到 Bob: {}分", it->second);
    } else {
        std::println("未找到 Bob");
    }

    // ✅ count —— 对 map 总是 0 或 1
    std::println("Bob 的个数: {}", m.count("Bob"));

// ✅ contains (C++20) —— 更语义化
#if __cplusplus >= 202002L
    if (m.contains("Alice")) {
        std::println("包含 Alice");
    }
#endif

    // ✅ at —— 带异常检查
    try {
        [[maybe_unused]] int score = m.at("Charlie");
        std::println("Charlie: {}分", score);
        score = m.at("Unknown"); // 抛出 std::out_of_range
    } catch (const std::out_of_range& e) {
        std::println("at('Unknown'): {}", e.what());
    }

    // ✅ erase by key
    size_t erased = m.erase("Bob"); // 返回删除的元素个数（0或1）
    std::println("删除 Bob: 删除了 {} 个元素", erased);

    // ✅ erase by iterator
    auto it2 = m.find("Diana");
    if (it2 != m.end()) {
        m.erase(it2); // 删除 Diana
    }

    // ✅ erase by range
    auto start = m.lower_bound("A"); // 第一个 >= "A"
    auto end = m.upper_bound("C"); // 第一个 > "C"
    m.erase(start, end); // 删除 [A, C] 范围内所有键

    print_map(m, "删除后");
}

// 示例 4: 范围查询与遍历
void example_range_iterate()
{
    std::println("\n=== 示例 4: 范围查询与遍历 ===");

    std::map<int, std::string> m {
        { 85, "Bob" },
        { 90, "Diana" },
        { 92, "Charlie" },
        { 95, "Alice" },
        { 98, "Eve" }
    };

    print_map(m, "成绩表");

    // ✅ lower_bound —— 第一个 >= key
    auto lb = m.lower_bound(90);
    std::println("lower_bound(90): {} -> {}", lb->first, lb->second);

    // ✅ upper_bound —— 第一个 > key
    auto ub = m.upper_bound(92);
    std::println("upper_bound(92): {} -> {}", ub->first, ub->second);

    // ✅ equal_range —— [lower_bound, upper_bound)
    auto [low, high] = m.equal_range(90);
    std::println("equal_range(90): [{}, {}) -> [{}, {})",
        low->first, high->first,
        low->second, high != m.end() ? high->second : "end");

    // ✅ 范围遍历：打印所有分数 >=90 且 <95 的学生
    std::println("分数在 [90, 95) 的学生:");
    auto range_start = m.lower_bound(90);
    auto range_end = m.lower_bound(95); // 注意：不是 upper_bound(95)!
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

// 示例 5: 自定义键类型
void example_custom_key()
{
    std::println("\n=== 示例 5: 自定义键类型 ===");

    std::map<StudentID, StudentInfo> student_db;
    student_db.emplace(StudentID(101), StudentInfo("Alice", 95));
    student_db.emplace(StudentID(103), StudentInfo("Bob", 87));
    student_db.emplace(StudentID(102), StudentInfo("Charlie", 92));

    std::println("学生数据库 (按ID排序):");
    for (const auto& [id, info] : student_db) {
        std::println("  ID {}: {} ({}分)", id.id, info.name, info.grade);
    }

    // ✅ 查找
    auto it = student_db.find(StudentID(102));
    if (it != student_db.end()) {
        std::println("找到 ID 102: {} ({}分)", it->second.name, it->second.grade);
    }
}

// 示例 6: 与 STL 算法配合
void example_algorithms()
{
    std::println("\n=== 示例 6: 与 STL 算法配合 ===");

    std::map<std::string, int> m {
        { "apple", 3 },
        { "banana", 5 },
        { "cherry", 2 }
    };

    // ✅ for_each —— 遍历并修改值
    std::for_each(m.begin(), m.end(), [](auto& pair) {
        pair.second *= 2; // 数量翻倍
    });
    print_map(m, "数量翻倍后");

    // ✅ transform —— 创建新 map（键不变，值变换）
    std::map<std::string, std::string> desc_map;
    std::transform(m.begin(), m.end(), std::inserter(desc_map, desc_map.begin()),
        [](const auto& pair) {
            return std::make_pair(pair.first, "count=" + std::to_string(pair.second));
        });
    print_map(desc_map, "描述性 map");

    // ✅ accumulate —— 计算总数量
    int total = std::accumulate(m.begin(), m.end(), 0,
        [](int sum, const auto& pair) { return sum + pair.second; });
    std::println("总数量: {}", total);
}

// 示例 7: 性能与使用建议
void example_performance()
{
    std::println("\n=== 示例 7: 性能与使用建议 ===");

    std::println("std::map 特性总结:");
    std::println("  - 底层: 红黑树");
    std::println("  - 插入/删除/查找: O(log n)");
    std::println("  - 自动排序: 按键排序");
    std::println("  - 键唯一: 不允许重复键");
    std::println("  - 迭代器稳定: 插入/删除不影响其他迭代器");
    std::println("  - 内存开销: 每个节点有左右指针 + 颜色位");

    std::println("\n何时使用 map:");
    std::println("  - 需要键值对映射 + 自动按键排序");
    std::println("  - 频繁查找/插入/删除，且数据量较大");
    std::println("  - 需要范围查询（如‘分数>90的所有学生’）");

    std::println("\n何时不使用 map:");
    std::println("  - 不需要排序 → 用 unordered_map（哈希表，平均 O(1)）");
    std::println("  - 允许重复键 → 用 multimap");
    std::println("  - 数据量小（< 100）→ 用 vector<pair> + 线性查找，可能更快");

    std::println("\n关键 API 选择:");
    std::println("  - 读取/修改已存在键 → operator[]");
    std::println("  - 插入新键（不覆盖）→ insert / emplace");
    std::println("  - 插入或覆盖 → insert_or_assign (C++17)");
    std::println("  - 不存在才构造 → try_emplace (C++17)");
    std::println("  - 安全读取 → at() 或 find()");
}
// 主函数
auto main(int argc, char* argv[]) -> int
{
    example_basic();
    example_insert_access();
    example_find_erase();
    example_range_iterate();
    example_custom_key();
    example_algorithms();
    example_performance();

    std::println("\n✅ std::map 学习完成！");
    return 0;
}