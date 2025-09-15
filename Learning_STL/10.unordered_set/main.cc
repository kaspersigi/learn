// ============================
// file: learn_std_unordered_set.cc
// 说明：全面学习 std::unordered_set 的现代 C++ 用法
// 编译：g++ -std=c++17 learn_std_unordered_set.cc -o learn_unordered_set
// ============================

#include <algorithm> // set_union, set_intersection 等
#include <functional> // std::hash, std::equal_to
#include <iterator> // std::inserter
#include <print> // C++23
#include <string>
#include <unordered_set>

// 辅助函数：打印容器（注意：无序，每次运行顺序可能不同！）
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
struct Point {
    int x, y;
    Point(int x, int y)
        : x(x)
        , y(y)
    {
    }

    // 用于 unordered_set 的相等比较
    bool operator==(const Point& other) const
    {
        return x == other.x && y == other.y;
    }
};

// 为 Point 提供哈希函数（特化 std::hash）
namespace std {
template <>
struct hash<Point> {
    size_t operator()(const Point& p) const
    {
        // 简单哈希：组合 x 和 y（实际项目建议用更好的哈希函数）
        return hash<int>()(p.x) ^ (hash<int>()(p.y) << 1);
    }
};
}

// 自定义哈希函数示例（用于字符串）
struct StringHash {
    size_t operator()(const std::string& s) const
    {
        size_t h = 0;
        for (char c : s) {
            h = h * 31 + c; // 简单多项式哈希
        }
        return h;
    }
};

// 自定义相等比较示例
struct StringEqual {
    bool operator()(const std::string& a, const std::string& b) const
    {
        return a == b;
    }
};

// 示例 1: 基本用法与初始化
void example_basic()
{
    std::println("\n=== 示例 1: 基本用法与初始化 ===");

    // ✅ 默认构造
    std::unordered_set<int> us1;
    us1.insert(3);
    us1.insert(1);
    us1.insert(4);
    us1.insert(1); // 重复，不会插入
    us1.insert(5);
    us1.insert(9);
    print_container(us1, "us1 (无序, 唯一)");

    // ✅ 初始化列表
    std::unordered_set<int> us2 { 5, 3, 8, 1, 9, 3, 5 }; // 自动去重
    print_container(us2, "us2 (初始化列表)");

    // ✅ 使用自定义哈希和相等比较
    std::unordered_set<std::string, StringHash, StringEqual> us3;
    us3.insert("apple");
    us3.insert("banana");
    us3.insert("apple"); // 重复，忽略
    us3.insert("cherry");
    print_container(us3, "us3 (自定义哈希)");

    // ✅ 指定桶数量和负载因子
    std::unordered_set<int> us4(10); // 预分配至少10个桶
    us4.insert({ 1, 2, 3, 4, 5 });
    print_container(us4, "us4 (预分配10桶)");

    // ✅ 拷贝构造
    std::unordered_set<int> us5 = us2;
    print_container(us5, "us5 (拷贝 us2)");
}

// 示例 2: 插入与删除
void example_insert_erase()
{
    std::println("\n=== 示例 2: 插入与删除 ===");

    std::unordered_set<int> us { 1, 3, 5, 7, 9 };

    print_container(us, "原始");

    // ✅ insert —— 返回 pair<iterator, bool>
    auto [it, success] = us.insert(5); // 尝试插入5（已存在）
    std::println("插入5: {}", success ? "成功" : "失败（已存在）");

    auto [it2, success2] = us.insert(6); // 插入6（新元素）
    std::println("插入6: {}, 值={}", success2 ? "成功" : "失败", *it2);

    print_container(us, "插入后");

    // ✅ erase by value
    size_t erased = us.erase(3); // 返回删除的元素个数（0或1）
    std::println("删除值3: 删除了 {} 个元素", erased);

    // ✅ erase by iterator
    auto it3 = us.find(7);
    if (it3 != us.end()) {
        us.erase(it3); // 删除7
    }

    print_container(us, "删除后");

    // ✅ clear
    us.clear();
    std::println("clear 后 size = {}", us.size());

    // ✅ rehash —— 强制重建哈希表（调整桶数量）
    us.rehash(20);
    std::println("rehash(20) 后 bucket_count = {}", us.bucket_count());
}

// 示例 3: 查找与哈希表信息
void example_find_info()
{
    std::println("\n=== 示例 3: 查找与哈希表信息 ===");

    std::unordered_set<int> us { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // ✅ find —— 平均 O(1)
    auto it = us.find(5);
    if (it != us.end()) {
        std::println("找到 5");
    } else {
        std::println("未找到 5");
    }

    // ✅ count —— 对 set 总是返回 0 或 1
    std::println("5 的个数: {}", us.count(5));

// ✅ contains (C++20) —— 更语义化
#if __cplusplus >= 202002L
    if (us.contains(3)) {
        std::println("包含 3");
    }
#endif

    // ✅ 哈希表信息
    std::println("size: {}", us.size());
    std::println("bucket_count: {}", us.bucket_count());
    std::println("load_factor: {:.2f}", us.load_factor());
    std::println("max_load_factor: {:.2f}", us.max_load_factor());

    // ✅ 遍历每个桶（调试用）
    std::println("各桶元素:");
    for (size_t i = 0; i < us.bucket_count(); ++i) {
        std::print("桶 {} (大小 {}): ", i, us.bucket_size(i));
        for (auto it = us.begin(i); it != us.end(i); ++it) {
            std::print("{} ", *it);
        }
        std::println("");
    }
}

// 示例 4: 自定义类型支持
void example_custom_type()
{
    std::println("\n=== 示例 4: 自定义类型支持 ===");

    std::unordered_set<Point> points;
    points.emplace(1, 2);
    points.emplace(3, 4);
    points.emplace(1, 2); // 重复，忽略
    points.emplace(5, 6);

    std::println("Points (无序):");
    for (const auto& p : points) {
        std::println("  ({}, {})", p.x, p.y);
    }

    // ✅ 查找
    Point target(3, 4);
    if (points.find(target) != points.end()) {
        std::println("找到点 (3,4)");
    }

    // ✅ 自定义最大负载因子
    points.max_load_factor(0.5); // 更低的负载因子 → 更少冲突，更多内存
    std::println("设置 max_load_factor=0.5 后: {:.2f}", points.load_factor());
}

// 示例 5: 与 STL 算法配合（集合运算）
void example_algorithms()
{
    std::println("\n=== 示例 5: STL 算法 —— 集合运算 ===");

    std::unordered_set<int> A { 1, 2, 3, 4, 5 };
    std::unordered_set<int> B { 4, 5, 6, 7, 8 };

    print_container(A, "集合 A");
    print_container(B, "集合 B");

    // ✅ 并集 A ∪ B
    std::unordered_set<int> union_set;
    std::set_union(A.begin(), A.end(), B.begin(), B.end(), std::inserter(union_set, union_set.begin()));
    print_container(union_set, "A ∪ B");

    // ✅ 交集 A ∩ B
    std::unordered_set<int> intersection_set;
    std::set_intersection(A.begin(), A.end(), B.begin(), B.end(), std::inserter(intersection_set, intersection_set.begin()));
    print_container(intersection_set, "A ∩ B");

    // ✅ 差集 A - B
    std::unordered_set<int> diff_set;
    std::set_difference(A.begin(), A.end(), B.begin(), B.end(), std::inserter(diff_set, diff_set.begin()));
    print_container(diff_set, "A - B");

    // ✅ 注意：由于无序，结果顺序不确定！
}

// 示例 6: 性能与使用建议
void example_performance()
{
    std::println("\n=== 示例 6: 性能与使用建议 ===");

    std::println("std::unordered_set 特性总结:");
    std::println("  - 底层: 哈希表（链地址法）");
    std::println("  - 插入/删除/查找: 平均 O(1)，最坏 O(n)");
    std::println("  - 无序: 遍历顺序不确定");
    std::println("  - 元素唯一: 不允许重复");
    std::println("  - 迭代器稳定性: ❌ 插入可能导致 rehash，使所有迭代器失效！");
    std::println("  - 内存开销: 较高（哈希桶 + 节点）");

    std::println("\n何时使用 unordered_set:");
    std::println("  - 需要快速查找/插入/删除，且不需要排序");
    std::println("  - 数据量大（> 1000），性能优势明显");
    std::println("  - 用作去重容器或存在性检查");

    std::println("\n何时不使用 unordered_set:");
    std::println("  - 需要有序遍历 → 用 set");
    std::println("  - 数据量小（< 100）→ 用 vector + sort/unique，可能更快");
    std::println("  - 频繁遍历 → 由于缓存不友好，可能比 vector/set 慢");

    std::println("\n性能优化建议:");
    std::println("  - 预分配桶数量: unordered_set(size_t n)");
    std::println("  - 设置合适的 max_load_factor (默认 1.0)");
    std::println("  - 提供高质量的哈希函数（避免冲突）");
    std::println("  - 避免在遍历时插入（可能导致 rehash 和迭代器失效）");
}

// 主函数
auto main(int argc, char* argv[]) -> int
{
    example_basic();
    example_insert_erase();
    example_find_info();
    example_custom_type();
    example_algorithms();
    example_performance();

    std::println("\n✅ std::unordered_set 学习完成！");
    return 0;
}