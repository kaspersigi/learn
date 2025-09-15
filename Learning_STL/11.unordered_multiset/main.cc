// ============================
// file: learn_std_unordered_multiset.cc
// 说明：全面学习 std::unordered_multiset 的现代 C++ 用法
// 编译：g++ -std=c++17 learn_std_unordered_multiset.cc -o learn_unordered_multiset
// ============================

#include <algorithm> // set_union, set_intersection 等
#include <functional> // std::hash, std::equal_to
#include <iterator> // std::inserter
#include <print> // C++23
#include <string>
#include <unordered_set> // unordered_multiset 在 <unordered_set> 中

// 辅助函数：打印容器（无序，顺序不确定）
template <typename Container>
void print_container(const Container& c, const char* label = "")
{
    if (*label)
        std::println("{}: ", label);
    for (const auto& elem : c) {
        std::print("{} ", elem);
    }
    std::println("");
}

// 自定义类型示例
struct Event {
    std::string type;
    int id;
    Event(std::string t, int i)
        : type(std::move(t))
        , id(i)
    {
    }

    bool operator==(const Event& other) const
    {
        return type == other.type && id == other.id;
    }
};

// 为 Event 提供哈希函数
namespace std {
template <>
struct hash<Event> {
    size_t operator()(const Event& e) const
    {
        return hash<string>()(e.type) ^ (hash<int>()(e.id) << 1);
    }
};
}

// 示例 1: 基本用法与初始化（允许重复！）
void example_basic()
{
    std::println("\n=== 示例 1: 基本用法与初始化（允许重复） ===");

    // ✅ 默认构造
    std::unordered_multiset<int> ums1;
    ums1.insert(3);
    ums1.insert(1);
    ums1.insert(4);
    ums1.insert(1); // 允许重复！
    ums1.insert(5);
    ums1.insert(9);
    ums1.insert(1); // 再次插入1
    print_container(ums1, "ums1 (无序, 允许重复)");

    // ✅ 初始化列表（重复元素全部保留）
    std::unordered_multiset<int> ums2 { 5, 3, 8, 1, 9, 3, 5, 3 }; // 3出现3次，5出现2次
    print_container(ums2, "ums2 (初始化列表)");

    // ✅ 指定桶数量
    std::unordered_multiset<int> ums3(10); // 预分配10个桶
    ums3.insert({ 1, 2, 2, 3, 3, 3 });
    print_container(ums3, "ums3 (预分配10桶)");

    // ✅ 拷贝构造
    std::unordered_multiset<int> ums4 = ums2;
    print_container(ums4, "ums4 (拷贝 ums2)");
}

// 示例 2: 插入与删除（注意：erase(key) 删除所有匹配值！）
void example_insert_erase()
{
    std::println("\n=== 示例 2: 插入与删除 ===");

    std::unordered_multiset<int> ums { 1, 2, 2, 3, 3, 3, 4, 4, 5 };

    print_container(ums, "原始");

    // ✅ insert —— 总是成功（无 bool 返回值）
    ums.insert(3); // 再插入一个3 → 现在有4个3
    ums.insert(2); // 再插入一个2 → 现在有3个2
    print_container(ums, "插入 3 和 2 后");

    // ✅ erase by value —— 删除所有等于该值的元素！
    size_t erased = ums.erase(3); // 删除所有3
    std::println("删除值3: 删除了 {} 个元素", erased);
    print_container(ums, "删除所有3后");

    // ✅ erase by iterator —— 只删除一个元素
    auto it = ums.find(2); // 找到第一个2
    if (it != ums.end()) {
        ums.erase(it); // 只删除这一个2
    }
    print_container(ums, "删除一个2后");

    // ✅ clear
    ums.clear();
    std::println("clear 后 size = {}", ums.size());
}

// 示例 3: 查找与计数（重点：count 可能 >1）
void example_find_count()
{
    std::println("\n=== 示例 3: 查找与计数 ===");

    std::unordered_multiset<int> ums { 1, 2, 2, 3, 3, 3, 4, 4, 5 };

    print_container(ums, "数据集");

    // ✅ find —— 返回任意一个匹配的迭代器（不保证是第一个！）
    auto it = ums.find(3);
    if (it != ums.end()) {
        std::println("find(3) 找到一个: {}", *it);
    }

    // ✅ count —— 返回匹配元素的个数（可能 >1）
    std::println("count(3): {} 个", ums.count(3));

    // ✅ equal_range —— 返回所有等于 key 的元素范围 [first, last)
    auto [first, last] = ums.equal_range(2);
    std::println("equal_range(2): 所有值为2的元素:");
    for (auto it = first; it != last; ++it) {
        std::print("{} ", *it);
    }
    std::println("");

// ✅ contains (C++20)
#if __cplusplus >= 202002L
    if (ums.contains(4)) {
        std::println("包含 4");
    }
#endif

    // ✅ 哈希表信息
    std::println("size: {}", ums.size());
    std::println("bucket_count: {}", ums.bucket_count());
    std::println("load_factor: {:.2f}", ums.load_factor());
}

// 示例 4: 自定义类型（允许“相等”元素）
void example_custom_type()
{
    std::println("\n=== 示例 4: 自定义类型 ===");

    std::unordered_multiset<Event> events;
    events.emplace("login", 101);
    events.emplace("click", 202);
    events.emplace("login", 101); // 重复事件！允许
    events.emplace("scroll", 303);
    events.emplace("login", 102); // 不同ID，不同事件

    std::println("Events (无序，允许重复):");
    for (const auto& e : events) {
        std::println("  {} #{}", e.type, e.id);
    }

    // ✅ 查找所有 "login" 事件（需要遍历或使用 equal_range）
    std::println("所有 login 事件:");
    auto [first, last] = events.equal_range(Event("login", 0)); // 注意：我们只关心 type
    // 🚨 问题：我们的 operator== 要求 type 和 id 都相等！
    // 所以 equal_range 只会找到完全相同的事件！

    // ✅ 解决方案：遍历所有元素
    for (const auto& e : events) {
        if (e.type == "login") {
            std::println("  {} #{}", e.type, e.id);
        }
    }

    // ✅ 或者：重新设计 Event 的比较逻辑（根据需求）
}

// 示例 5: 与 STL 算法配合（集合运算 —— 注意重复元素！）
void example_algorithms()
{
    std::println("\n=== 示例 5: STL 算法 —— 集合运算（注意重复！） ===");

    std::unordered_multiset<int> A { 1, 2, 2, 3, 3 };
    std::unordered_multiset<int> B { 2, 3, 3, 4, 4 };

    print_container(A, "多重集合 A");
    print_container(B, "多重集合 B");

    // ✅ 并集 A ∪ B —— 重复元素取最大出现次数
    std::unordered_multiset<int> union_ums;
    std::set_union(A.begin(), A.end(), B.begin(), B.end(), std::inserter(union_ums, union_ums.begin()));
    print_container(union_ums, "A ∪ B (多重集并集)");

    // ✅ 交集 A ∩ B —— 重复元素取最小出现次数
    std::unordered_multiset<int> intersection_ums;
    std::set_intersection(A.begin(), A.end(), B.begin(), B.end(), std::inserter(intersection_ums, intersection_ums.begin()));
    print_container(intersection_ums, "A ∩ B (多重集交集)");

    // ✅ 差集 A - B —— 对每个元素，次数 = max(0, countA - countB)
    std::unordered_multiset<int> diff_ums;
    std::set_difference(A.begin(), A.end(), B.begin(), B.end(), std::inserter(diff_ums, diff_ums.begin()));
    print_container(diff_ums, "A - B (多重集差集)");

    // ✅ 对称差集 —— (A-B) ∪ (B-A)
    std::unordered_multiset<int> sym_diff_ums;
    std::set_symmetric_difference(A.begin(), A.end(), B.begin(), B.end(), std::inserter(sym_diff_ums, sym_diff_ums.begin()));
    print_container(sym_diff_ums, "A △ B (多重集对称差集)");
}

// 示例 6: 性能与使用建议
void example_performance()
{
    std::println("\n=== 示例 6: 性能与使用建议 ===");

    std::println("std::unordered_multiset 特性总结:");
    std::println("  - 底层: 哈希表（同 unordered_set）");
    std::println("  - 插入/删除/查找: 平均 O(1)，最坏 O(n)");
    std::println("  - 无序: 遍历顺序不确定");
    std::println("  - 允许重复: 同一值可多次插入");
    std::println("  - 迭代器稳定性: ❌ 插入可能导致 rehash，使所有迭代器失效！");

    std::println("\n何时使用 unordered_multiset:");
    std::println("  - 需要维护一个无序的多重集合（允许重复）");
    std::println("  - 频繁插入/删除/查找，且性能优先于排序");
    std::println("  - 数据量大（> 1000），哈希表优势明显");

    std::println("\n何时不使用 unordered_multiset:");
    std::println("  - 需要排序 → 用 multiset");
    std::println("  - 数据量小 → 用 vector + sort，可能更快");
    std::println("  - 只需计数 → 用 unordered_map<key, count>");

    std::println("\n与 unordered_set 的关键区别:");
    std::println("  - unordered_set::insert 返回 pair<iterator, bool>");
    std::println("  - unordered_multiset::insert 返回 iterator（总是成功）");
    std::println("  - unordered_set::erase(key) 返回 size_t（0或1）");
    std::println("  - unordered_multiset::erase(key) 返回 size_t（删除的元素个数，可能>1）");
    std::println("  - unordered_set::count(key) 返回 0 或 1");
    std::println("  - unordered_multiset::count(key) 返回出现次数（可能>1）");
}

// 主函数
auto main(int argc, char* argv[]) -> int
{
    example_basic();
    example_insert_erase();
    example_find_count();
    example_custom_type();
    example_algorithms();
    example_performance();

    std::println("\n✅ std::unordered_multiset 学习完成！");
    return 0;
}