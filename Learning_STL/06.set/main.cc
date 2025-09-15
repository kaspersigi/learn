// ============================
// file: learn_std_set.cc
// 说明：全面学习 std::set 的现代 C++ 用法
// 编译：g++ -std=c++17 learn_std_set.cc -o learn_set
// ============================

#include <algorithm> // set_union, set_intersection 等
#include <iterator> // std::inserter
#include <print> // C++23
#include <set>
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
struct Person {
    std::string name;
    int age;

    Person(std::string n, int a)
        : name(std::move(n))
        , age(a)
    {
    }

    // 必须提供比较操作 —— set 依赖这个排序
    auto operator<=>(const Person&) const = default; // C++20 三路比较
    // C++17 及以前需手动重载 operator<
    // bool operator<(const Person& other) const {
    //     return age < other.age; // 按年龄排序
    // }
};

// 自定义比较器示例
struct DescendingInt {
    bool operator()(int a, int b) const
    {
        return a > b; // 降序
    }
};

// 示例 1: 基本用法与初始化
void example_basic()
{
    std::println("\n=== 示例 1: 基本用法与初始化 ===");

    // ✅ 默认构造（升序，唯一）
    std::set<int> s1;
    s1.insert(3);
    s1.insert(1);
    s1.insert(4);
    s1.insert(1); // 重复，不会插入
    s1.insert(5);
    s1.insert(9);
    print_container(s1, "s1 (升序, 唯一)");

    // ✅ 初始化列表
    std::set<int> s2 { 5, 3, 8, 1, 9, 3, 5 }; // 自动去重+排序
    print_container(s2, "s2 (初始化列表)");

    // ✅ 使用自定义比较器（降序）
    std::set<int, DescendingInt> s3 { 5, 3, 8, 1, 9 };
    print_container(s3, "s3 (降序)");

    // ✅ 使用 lambda 作为比较器（C++14+）
    auto cmp = [](const std::string& a, const std::string& b) {
        return a.length() < b.length(); // 按长度排序
    };
    std::set<std::string, decltype(cmp)> s4(cmp);
    s4.insert("hi");
    s4.insert("hello");
    s4.insert("a");
    s4.insert("world");
    print_container(s4, "s4 (按字符串长度排序)");

    // ✅ 拷贝构造
    std::set<int> s5 = s2;
    print_container(s5, "s5 (拷贝 s2)");
}

// 示例 2: 插入与删除
void example_insert_erase()
{
    std::println("\n=== 示例 2: 插入与删除 ===");

    std::set<int> s { 1, 3, 5, 7, 9 };

    print_container(s, "原始");

    // ✅ insert —— 返回 pair<iterator, bool>
    auto [it, success] = s.insert(5); // 尝试插入5（已存在）
    std::println("插入5: {}", success ? "成功" : "失败（已存在）");

    auto [it2, success2] = s.insert(6); // 插入6（新元素）
    std::println("插入6: {}, 值={}", success2 ? "成功" : "失败", *it2);

    print_container(s, "插入后");

    // ✅ erase by value
    size_t erased = s.erase(3); // 返回删除的元素个数（0或1）
    std::println("删除值3: 删除了 {} 个元素", erased);

    // ✅ erase by iterator
    auto it3 = s.find(7);
    if (it3 != s.end()) {
        s.erase(it3); // 删除7
    }

    print_container(s, "删除后");

    // ✅ erase by range
    auto start = s.lower_bound(5); // 第一个 >=5 的迭代器
    auto end = s.upper_bound(8); // 第一个 >8 的迭代器
    s.erase(start, end); // 删除 [5, 8] 范围内元素
    print_container(s, "范围删除 [5,8] 后");

    // ✅ clear
    s.clear();
    std::println("clear 后 size = {}", s.size());
}

// 示例 3: 查找与范围查询
void example_find_range()
{
    std::println("\n=== 示例 3: 查找与范围查询 ===");

    std::set<int> s { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // ✅ find —— O(log n)
    auto it = s.find(5);
    if (it != s.end()) {
        std::println("找到 5");
    } else {
        std::println("未找到 5");
    }

    // ✅ count —— 对 set 总是返回 0 或 1
    std::println("5 的个数: {}", s.count(5));

    // ✅ lower_bound —— 第一个 >= key 的元素
    auto lb = s.lower_bound(5);
    std::println("lower_bound(5): {}", lb != s.end() ? std::to_string(*lb) : "end");

    // ✅ upper_bound —— 第一个 > key 的元素
    auto ub = s.upper_bound(5);
    std::println("upper_bound(5): {}", ub != s.end() ? std::to_string(*ub) : "end");

    // ✅ equal_range —— 返回 [lower_bound, upper_bound) 的 pair
    auto [low, high] = s.equal_range(5);
    std::println("equal_range(5): [{}, {})",
        low != s.end() ? std::to_string(*low) : "end",
        high != s.end() ? std::to_string(*high) : "end");

    // ✅ 范围遍历：打印所有 >3 且 <=7 的元素
    std::println("范围 (3,7]:");
    auto range_start = s.upper_bound(3); // >3
    auto range_end = s.upper_bound(7); // >7
    for (auto it = range_start; it != range_end; ++it) {
        std::print("{} ", *it);
    }
    std::println("");
}

// 示例 4: 自定义类型与比较器
void example_custom_type()
{
    std::println("\n=== 示例 4: 自定义类型与比较器 ===");

    // ✅ 按年龄排序的 Person set
    std::set<Person> people {
        { "Alice", 30 },
        { "Bob", 25 },
        { "Charlie", 35 },
        { "Diana", 25 } // 注意：25 重复，但 Person 不同，会插入吗？
    };

    // 🚨 重要：因为 Person 的 operator< 是按 age 比较的，
    // 所以 {"Bob",25} 和 {"Diana",25} 被认为是“相等”的（因为 !(a<b) && !(b<a)）
    // 因此 Diana 不会被插入！

    std::println("People (按年龄排序，年龄相同时视为重复):");
    for (const auto& p : people) {
        std::println("  {}: {}岁", p.name, p.age);
    }

    // ✅ 解决方案：定义更精细的比较器（年龄相同时按名字排序）
    auto cmp = [](const Person& a, const Person& b) {
        if (a.age != b.age)
            return a.age < b.age;
        return a.name < b.name;
    };
    std::set<Person, decltype(cmp)> people2(cmp);
    people2.insert({ "Alice", 30 });
    people2.insert({ "Bob", 25 });
    people2.insert({ "Charlie", 35 });
    people2.insert({ "Diana", 25 }); // 现在会插入，因为名字不同

    std::println("People2 (按年龄，年龄相同时按名字):");
    for (const auto& p : people2) {
        std::println("  {}: {}岁", p.name, p.age);
    }
}

// 示例 5: 与 STL 算法配合（集合运算）
void example_algorithms()
{
    std::println("\n=== 示例 5: STL 算法 —— 集合运算 ===");

    std::set<int> A { 1, 2, 3, 4, 5 };
    std::set<int> B { 4, 5, 6, 7, 8 };

    print_container(A, "集合 A");
    print_container(B, "集合 B");

    // ✅ 并集 A ∪ B
    std::set<int> union_set;
    std::set_union(A.begin(), A.end(), B.begin(), B.end(), std::inserter(union_set, union_set.begin()));
    print_container(union_set, "A ∪ B");

    // ✅ 交集 A ∩ B
    std::set<int> intersection_set;
    std::set_intersection(A.begin(), A.end(), B.begin(), B.end(), std::inserter(intersection_set, intersection_set.begin()));
    print_container(intersection_set, "A ∩ B");

    // ✅ 差集 A - B
    std::set<int> diff_set;
    std::set_difference(A.begin(), A.end(), B.begin(), B.end(), std::inserter(diff_set, diff_set.begin()));
    print_container(diff_set, "A - B");

    // ✅ 对称差集 (A - B) ∪ (B - A)
    std::set<int> sym_diff_set;
    std::set_symmetric_difference(A.begin(), A.end(), B.begin(), B.end(), std::inserter(sym_diff_set, sym_diff_set.begin()));
    print_container(sym_diff_set, "A △ B");
}

// 示例 6: 迭代器与遍历（有序！）
void example_iterators()
{
    std::println("\n=== 示例 6: 迭代器与遍历 ===");

    std::set<int> s { 5, 2, 8, 1, 9 };

    // ✅ 正向迭代（自动有序）
    std::println("Forward (sorted):");
    for (auto it = s.begin(); it != s.end(); ++it) {
        std::print("{} ", *it);
    }
    std::println("");

    // ✅ 反向迭代
    std::println("Reverse:");
    for (auto it = s.rbegin(); it != s.rend(); ++it) {
        std::print("{} ", *it);
    }
    std::println("");

    // ✅ 范围 for
    std::println("Range-for:");
    for (const auto& x : s) {
        std::print("{} ", x);
    }
    std::println("");

    // ❌ 不支持随机访问！
    // s[2]; // 编译错误！
    // 但可以用 std::advance（O(n)）
    auto it = s.begin();
    std::advance(it, 2);
    std::println("第3小的元素: {}", *it);
}

// 示例 7: 性能与使用建议
void example_performance()
{
    std::println("\n=== 示例 7: 性能与使用建议 ===");

    std::println("std::set 特性总结:");
    std::println("  - 底层: 红黑树（平衡BST）");
    std::println("  - 插入/删除/查找: O(log n)");
    std::println("  - 自动排序: 总是有序");
    std::println("  - 元素唯一: 不允许重复");
    std::println("  - 迭代器稳定: 插入/删除不影响其他迭代器");
    std::println("  - 内存开销: 每个节点有左右指针 + 颜色位");

    std::println("\n何时使用 set:");
    std::println("  - 需要动态维护一个有序、无重复的集合");
    std::println("  - 频繁查找、插入、删除，且数据量较大");
    std::println("  - 需要前驱/后继查询（lower_bound/upper_bound）");

    std::println("\n何时不使用 set:");
    std::println("  - 数据量小（< 100）→ 用 vector + sort/unique");
    std::println("  - 不需要排序 → 用 unordered_set（哈希表，平均 O(1)）");
    std::println("  - 允许重复 → 用 multiset");
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

    std::println("\n✅ std::set 学习完成！");
    return 0;
}