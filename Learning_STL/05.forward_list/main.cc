// ============================
// file: learn_std_forward_list.cc
// 说明：全面学习 std::forward_list 的现代 C++ 用法
// 编译：g++ -std=c++17 learn_std_forward_list.cc -o learn_forward_list
// ============================

#include <algorithm> // find, remove_if, transform
#include <forward_list>
#include <iterator> // std::distance, std::ostream_iterator
#include <numeric> // accumulate (需手动计算)
#include <print> // C++23 (可选)

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

// 自定义类型（带日志）
struct Node {
    int id;
    Node(int i)
        : id(i)
    {
        std::println("Node({}) constructed", i);
    }
    Node(const Node& other)
        : id(other.id)
    {
        std::println("Node({}) copy-constructed", id);
    }
    Node(Node&& other) noexcept
        : id(other.id)
    {
        std::println("Node({}) move-constructed", id);
    }
    ~Node() { std::println("Node({}) destructed", id); }
    auto operator<=>(const Node&) const = default;
    bool operator==(const Node& other) const { return id == other.id; }
};

// 辅助函数：计算 forward_list 大小（因为 .size() 可能不存在或 O(n)）
template <typename T>
size_t fl_size(const std::forward_list<T>& fl)
{
    return std::distance(fl.begin(), fl.end());
}

// 示例 1: 初始化方式
void example_init()
{
    std::println("\n=== 示例 1: 初始化方式 ===");

    // ✅ 默认构造
    std::forward_list<int> fl1;
    std::println("fl1 大小: {}", fl_size(fl1));

    // ✅ 初始化列表
    std::forward_list<int> fl2 { 1, 2, 3, 4, 5 };
    print_container(fl2, "fl2");

    // ✅ 从迭代器范围构造
    std::forward_list<int> fl3(fl2.begin(), ++(++fl2.begin())); // 前两个元素
    print_container(fl3, "fl3 (range: first 2)");

    // ✅ 拷贝构造
    std::forward_list<int> fl4 = fl2;
    print_container(fl4, "fl4 (copy)");

    // ❌ 不能指定大小初始化（无 fill 构造函数）
    // std::forward_list<int> fl5(5, 99); // 编译错误！
}

// 示例 2: 前端操作（核心）
void example_front_operations()
{
    std::println("\n=== 示例 2: 前端操作 ===");

    std::forward_list<int> fl;

    // ✅ push_front / emplace_front
    fl.push_front(3);
    fl.push_front(2);
    fl.emplace_front(1); // 直接构造

    print_container(fl, "After push/emplace front: 1,2,3");

    // ✅ 访问前端
    std::println("front: {}", fl.front());

    // ✅ pop_front
    fl.pop_front();
    print_container(fl, "After pop_front: 2,3");
}

// 示例 3: 任意位置插入/删除 —— 需要“前一个元素”的迭代器
void example_insert_erase()
{
    std::println("\n=== 示例 3: 任意位置插入/删除 ===");

    std::forward_list<int> fl { 10, 20, 30, 40 };
    print_container(fl, "原始");

    // ✅ 获取指向 20 的迭代器（我们需要插入到 20 之后，即 30 之前）
    auto prev_it = fl.begin(); // 指向10
    auto it = prev_it;
    ++it; // 指向20
    // 现在 prev_it 是 "before 20"，it 是 "20"

    // ✅ insert_after —— 在 it 之后插入（即 20 之后）
    fl.insert_after(it, 99); // 插入到20之后 → 10,20,99,30,40
    print_container(fl, "insert_after 20: 99");

    // ✅ erase_after —— 删除 it 之后的元素（即99）
    fl.erase_after(it); // 删除99 → 10,20,30,40
    print_container(fl, "erase_after 20: removed 99");

    // ✅ insert_after 多个元素
    fl.insert_after(it, 3, 88); // 在20之后插入3个88 → 10,20,88,88,88,30,40
    print_container(fl, "insert_after 20: 3x88");

    // ✅ insert_after 初始化列表
    fl.insert_after(fl.before_begin(), { 1, 2 }); // 在开头前插入 → 1,2,10,20,...
    print_container(fl, "insert_after before_begin: {1,2}");

    // ✅ clear
    fl.clear();
    std::println("clear 后大小: {}", fl_size(fl));
}

// 示例 4: 迭代与遍历（单向！）
void example_iterators()
{
    std::println("\n=== 示例 4: 迭代与遍历 ===");

    std::forward_list<char> fl { 'A', 'B', 'C', 'D' };

    // ✅ 正向迭代
    std::println("Forward:");
    for (auto it = fl.begin(); it != fl.end(); ++it) {
        std::print("{} ", *it);
    }
    std::println("");

    // ❌ 无反向迭代器！
    // for (auto it = fl.rbegin(); ...) // 编译错误！

    // ✅ 范围 for
    std::println("Range-for:");
    for (const auto& c : fl) {
        std::print("{} ", c);
    }
    std::println("");

    // ✅ before_begin() —— 获取“头前”迭代器（用于 insert_after/begin 前）
    auto bit = fl.before_begin();
    fl.insert_after(bit, 'X'); // 在开头插入X
    print_container(fl, "insert_after before_begin: X");

    // ❌ 不支持随机访问！
    // fl[2];        // 编译错误！
    // 不能用 std::advance 快速跳转？可以，但仍是 O(n)
    auto it = fl.begin();
    std::advance(it, 2); // O(n) 时间！
    std::println("Element at 'index' 2: {}", *it);
}

// 示例 5: forward_list 专属算法 —— sort, merge, unique, remove, reverse
void example_fl_algorithms()
{
    std::println("\n=== 示例 5: forward_list 专属算法 ===");

    std::forward_list<int> fl { 4, 1, 9, 0, 5, 0, 3, 0, 2, 8 };
    print_container(fl, "原始数据");

    // ✅ sort —— 成员函数（利用链表结构）
    fl.sort();
    print_container(fl, "排序后（fl.sort）");

    // ✅ unique —— 移除连续重复（需先排序）
    fl.unique();
    print_container(fl, "去重后（fl.unique）");

    // ✅ remove —— 移除所有等于某值的元素
    fl.remove(0);
    print_container(fl, "移除所有0后（fl.remove）");

    // ✅ remove_if —— 移除满足条件的元素
    fl.remove_if([](int x) { return x % 2 == 0; }); // 移除偶数
    print_container(fl, "移除偶数后（fl.remove_if）");

    // ✅ merge —— 合并两个已排序的 forward_list
    std::forward_list<int> fl2 { 2, 4, 6, 8 };
    fl2.sort();
    fl.merge(fl2); // 合并 fl2 到 fl（fl2 变为空）
    print_container(fl, "合并 fl2 后");
    std::println("fl2 大小 after merge: {}", fl_size(fl2));

    // ✅ reverse —— 反转整个 list
    fl.reverse();
    print_container(fl, "反转后（fl.reverse）");

    // ✅ splice_after —— 剪切另一个 fl 的元素（O(1)）
    std::forward_list<int> source { 100, 200, 300 };
    auto s_it = source.before_begin(); // 指向100之前
    std::advance(s_it, 1); // 现在指向100（因为 before_begin +1 = begin）

    auto dest_it = fl.before_begin();
    fl.splice_after(dest_it, source, s_it); // 剪切 source 中 s_it 之后的元素（200,300）
    print_container(fl, "splice_after 200,300 to front");
    print_container(source, "source after splice (100 remains)");
}

// 示例 6: 与通用 STL 算法配合
void example_std_algorithms()
{
    std::println("\n=== 示例 6: 与 STL 算法配合 ===");

    std::forward_list<int> fl { 1, 2, 3, 4, 5, 6, 7, 8 };

    // ✅ find —— 支持
    auto it = std::find(fl.begin(), fl.end(), 5);
    if (it != fl.end()) {
        std::println("找到 5");
    }

    // ✅ accumulate —— 支持，但需手动指定范围
    int sum = std::accumulate(fl.begin(), fl.end(), 0);
    std::println("总和: {}", sum);

    // ❌ 不能用 std::sort —— 因为 forward_list 迭代器不是随机访问迭代器
    // std::sort(fl.begin(), fl.end()); // 编译错误！

    // ✅ 但可以用 fl.sort()（见上例）

    // ✅ transform —— 需目标容器大小匹配（但 forward_list 无 resize，需用 insert）
    std::forward_list<int> result;
    auto in_it = fl.begin();
    auto out_it = result.before_begin();
    while (in_it != fl.end()) {
        out_it = result.insert_after(out_it, (*in_it) * (*in_it));
        ++in_it;
    }
    print_container(result, "平方后（手动 transform）");

    // ✅ copy —— 支持
    std::forward_list<int> copy_fl;
    auto copy_out = copy_fl.before_begin();
    for (auto x : fl) {
        copy_out = copy_fl.insert_after(copy_out, x);
    }
    print_container(copy_fl, "拷贝后（手动 copy）");
}

// 示例 7: 移动语义与自定义类型
void example_move()
{
    std::println("\n=== 示例 7: 移动语义与自定义类型 ===");

    std::forward_list<Node> nodes;

    // ✅ push_front —— 可能 move
    nodes.push_front(Node(1));

    // ✅ emplace_front —— 直接构造
    nodes.emplace_front(2);

    // ✅ insert_after —— 需要迭代器
    auto it = nodes.before_begin();
    nodes.emplace_after(it, 3); // 在开头插入3 → 3,2,1

    std::println("nodes 大小: {}", fl_size(nodes));

    // ✅ 析构自动调用
}

// 示例 8: 性能与内存对比（概念性说明）
void example_performance()
{
    std::println("\n=== 示例 8: 性能与内存对比 ===");

    std::println("std::forward_list vs std::list:");
    std::println("  - 每个节点内存: forward_list ≈ sizeof(T) + sizeof(ptr)");
    std::println("                 list        ≈ sizeof(T) + 2*sizeof(ptr)");
    std::println("  - 不支持: size(), push_back(), pop_back(), 反向迭代");
    std::println("  - 适用: 内存敏感、单向遍历、前端/中间插入频繁");

    std::println("\n一般建议:");
    std::println("  - 优先 vector/deque");
    std::println("  - 仅当 list 的双向功能多余，且内存敏感时，才用 forward_list");
}

// 主函数
auto main(int argc, char* argv[]) -> int
{
    example_init();
    example_front_operations();
    example_insert_erase();
    example_iterators();
    example_fl_algorithms();
    example_std_algorithms();
    example_move();
    example_performance();

    std::println("\n✅ std::forward_list 学习完成！");
    return 0;
}