// ============================
// file: learn_std_multiset.cc
// 说明：全面学习 std::multiset 的现代 C++ 用法
// 编译：g++ -std=c++17 learn_std_multiset.cc -o learn_multiset
// ============================

#include <algorithm> // set_union, set_intersection 等
#include <functional> // std::greater
#include <iterator> // std::inserter
#include <print> // C++23
#include <set> // multiset 在 <set> 头文件中
#include <string>

// 辅助函数：打印容器
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
struct Score {
    std::string name;
    int points;

    Score(std::string n, int p)
        : name(std::move(n))
        , points(p)
    {
    }

    // 按分数排序（允许同分）
    auto operator<=>(const Score&) const = default;
    // C++17: bool operator<(const Score& other) const { return points < other.points; }
};

// 示例 1: 基本用法与初始化（允许重复！）
void example_basic()
{
    std::println("\n=== 示例 1: 基本用法与初始化（允许重复） ===");

    // ✅ 默认构造
    std::multiset<int> ms1;
    ms1.insert(3);
    ms1.insert(1);
    ms1.insert(4);
    ms1.insert(1); // 允许重复！
    ms1.insert(5);
    ms1.insert(9);
    ms1.insert(1); // 再次插入1
    print_container(ms1, "ms1 (升序, 允许重复)");

    // ✅ 初始化列表（重复元素全部保留）
    std::multiset<int> ms2 { 5, 3, 8, 1, 9, 3, 5, 3 }; // 3出现3次，5出现2次
    print_container(ms2, "ms2 (初始化列表)");

    // ✅ 使用自定义比较器（降序）
    std::multiset<int, std::greater<int>> ms3 { 5, 3, 8, 1, 9, 3, 5 };
    print_container(ms3, "ms3 (降序)");

    // ✅ 拷贝构造
    std::multiset<int> ms4 = ms2;
    print_container(ms4, "ms4 (拷贝 ms2)");
}

// 示例 2: 插入与删除（注意：删除所有匹配值！）
void example_insert_erase()
{
    std::println("\n=== 示例 2: 插入与删除 ===");

    std::multiset<int> ms { 1, 2, 2, 3, 3, 3, 4, 4, 5 };

    print_container(ms, "原始");

    // ✅ insert —— 总是成功（无 bool 返回值）
    ms.insert(3); // 再插入一个3 → 现在有4个3
    ms.insert(2); // 再插入一个2 → 现在有3个2
    print_container(ms, "插入 3 和 2 后");

    // ✅ erase by value —— 删除所有等于该值的元素！
    size_t erased = ms.erase(3); // 删除所有3
    std::println("删除值3: 删除了 {} 个元素", erased);
    print_container(ms, "删除所有3后");

    // ✅ erase by iterator —— 只删除一个元素
    auto it = ms.find(2); // 找到第一个2
    if (it != ms.end()) {
        ms.erase(it); // 只删除这一个2
    }
    print_container(ms, "删除一个2后");

    // ✅ erase by range
    auto start = ms.lower_bound(4); // 第一个 >=4
    auto end = ms.upper_bound(4); // 第一个 >4 → 即所有4的结尾
    ms.erase(start, end); // 删除所有4
    print_container(ms, "删除所有4后");

    // ✅ clear
    ms.clear();
    std::println("clear 后 size = {}", ms.size());
}

// 示例 3: 查找与范围查询（重点：equal_range！）
void example_find_range()
{
    std::println("\n=== 示例 3: 查找与范围查询 ===");

    std::multiset<int> ms { 1, 2, 2, 3, 3, 3, 4, 4, 5 };

    print_container(ms, "数据集");

    // ✅ find —— 返回第一个匹配的迭代器
    auto it = ms.find(3);
    if (it != ms.end()) {
        std::println("find(3) 找到第一个: {}", *it);
    }

    // ✅ count —— 返回匹配元素的个数
    std::println("count(3): {} 个", ms.count(3));

    // ✅ lower_bound —— 第一个 >= key
    auto lb = ms.lower_bound(3);
    std::println("lower_bound(3): {}", lb != ms.end() ? std::to_string(*lb) : "end");

    // ✅ upper_bound —— 第一个 > key
    auto ub = ms.upper_bound(3);
    std::println("upper_bound(3): {}", ub != ms.end() ? std::to_string(*ub) : "end");

    // ✅ equal_range —— 返回 [first, last) 所有等于 key 的元素范围
    auto [first, last] = ms.equal_range(3);
    std::println("equal_range(3): 从 {} 到 {}",
        first != ms.end() ? std::to_string(*first) : "end",
        last != ms.end() ? std::to_string(*last) : "end");

    // ✅ 遍历所有等于3的元素
    std::println("所有值为3的元素:");
    for (auto it = first; it != last; ++it) {
        std::print("{} ", *it);
    }
    std::println("");

    // ✅ 范围遍历：打印所有 >=2 且 <5 的元素
    std::println("范围 [2,5):");
    auto range_start = ms.lower_bound(2);
    auto range_end = ms.lower_bound(5); // 注意：不是 upper_bound(5)!
    for (auto it = range_start; it != range_end; ++it) {
        std::print("{} ", *it);
    }
    std::println("");
}

// 示例 4: 自定义类型（允许“相等”元素）
void example_custom_type()
{
    std::println("\n=== 示例 4: 自定义类型 ===");

    std::multiset<Score> scores;
    scores.emplace("Alice", 95);
    scores.emplace("Bob", 85);
    scores.emplace("Charlie", 95); // 同分！允许
    scores.emplace("Diana", 85); // 同分！允许
    scores.emplace("Eve", 90);

    std::println("Scores (按分数排序，允许同分):");
    for (const auto& s : scores) {
        std::println("  {}: {}分", s.name, s.points);
    }

    // ✅ 查找所有85分的学生
    auto [first, last] = scores.equal_range(Score("", 85));
    std::println("所有85分的学生:");
    for (auto it = first; it != last; ++it) {
        std::println("  {}", it->name);
    }
}

// 示例 5: 与 STL 算法配合（集合运算 —— 注意重复元素！）
void example_algorithms()
{
    std::println("\n=== 示例 5: STL 算法 —— 集合运算（注意重复！） ===");

    std::multiset<int> A { 1, 2, 2, 3, 3 };
    std::multiset<int> B { 2, 3, 3, 4, 4 };

    print_container(A, "多重集合 A");
    print_container(B, "多重集合 B");

    // ✅ 并集 A ∪ B —— 重复元素取最大出现次数
    // 1:1次, 2: max(2,1)=2次, 3: max(2,2)=2次, 4:2次 → {1,2,2,3,3,4,4}
    std::multiset<int> union_ms;
    std::set_union(A.begin(), A.end(), B.begin(), B.end(), std::inserter(union_ms, union_ms.begin()));
    print_container(union_ms, "A ∪ B (多重集并集)");

    // ✅ 交集 A ∩ B —— 重复元素取最小出现次数
    // 2: min(2,1)=1次, 3: min(2,2)=2次 → {2,3,3}
    std::multiset<int> intersection_ms;
    std::set_intersection(A.begin(), A.end(), B.begin(), B.end(), std::inserter(intersection_ms, intersection_ms.begin()));
    print_container(intersection_ms, "A ∩ B (多重集交集)");

    // ✅ 差集 A - B —— 对每个元素，次数 = max(0, countA - countB)
    // 1:1-0=1, 2:2-1=1, 3:2-2=0, 4:0-2=0 → {1,2}
    std::multiset<int> diff_ms;
    std::set_difference(A.begin(), A.end(), B.begin(), B.end(), std::inserter(diff_ms, diff_ms.begin()));
    print_container(diff_ms, "A - B (多重集差集)");

    // ✅ 对称差集 —— (A-B) ∪ (B-A)
    // A-B: {1,2}, B-A: {4,4} → {1,2,4,4}
    std::multiset<int> sym_diff_ms;
    std::set_symmetric_difference(A.begin(), A.end(), B.begin(), B.end(), std::inserter(sym_diff_ms, sym_diff_ms.begin()));
    print_container(sym_diff_ms, "A △ B (多重集对称差集)");
}

// 示例 6: 迭代器与遍历
void example_iterators()
{
    std::println("\n=== 示例 6: 迭代器与遍历 ===");

    std::multiset<int> ms { 5, 2, 8, 1, 9, 2, 5 };

    // ✅ 正向迭代（自动有序）
    std::println("Forward (sorted):");
    for (auto it = ms.begin(); it != ms.end(); ++it) {
        std::print("{} ", *it);
    }
    std::println("");

    // ✅ 反向迭代
    std::println("Reverse:");
    for (auto it = ms.rbegin(); it != ms.rend(); ++it) {
        std::print("{} ", *it);
    }
    std::println("");

    // ✅ 范围 for
    std::println("Range-for:");
    for (const auto& x : ms) {
        std::print("{} ", x);
    }
    std::println("");
}

// 示例 7: 性能与使用建议
void example_performance()
{
    std::println("\n=== 示例 7: 性能与使用建议 ===");

    std::println("std::multiset 特性总结:");
    std::println("  - 底层: 红黑树（同 set）");
    std::println("  - 插入/删除/查找: O(log n)");
    std::println("  - 自动排序: 总是有序");
    std::println("  - 允许重复: 同一值可多次插入");
    std::println("  - 迭代器稳定: 插入/删除不影响其他迭代器");

    std::println("\n何时使用 multiset:");
    std::println("  - 需要维护一个有序的多重集合（允许重复）");
    std::println("  - 频繁插入/删除/查找，且需保持有序");
    std::println("  - 需要范围查询（如‘所有等于x的元素’）");

    std::println("\n何时不使用 multiset:");
    std::println("  - 不需要排序 → 用 unordered_multiset（哈希表）");
    std::println("  - 数据量小 → 用 vector + sort，可能更快");
    std::println("  - 只需计数 → 用 unordered_map<key, count>");

    std::println("\n与 set 的关键区别:");
    std::println("  - set::insert 返回 pair<iterator, bool>");
    std::println("  - multiset::insert 返回 iterator（总是成功）");
    std::println("  - set::erase(key) 返回 size_t（0或1）");
    std::println("  - multiset::erase(key) 返回 size_t（删除的元素个数，可能>1）");
}

// 主函数
auto main(int argc, char* argv[]) -> int
{
    example_basic();
    example_insert_erase();
    example_find_range();
    example_custom_type();
    example_algorithms();
    example_iterators();
    example_performance();

    std::println("\n✅ std::multiset 学习完成！");
    return 0;
}