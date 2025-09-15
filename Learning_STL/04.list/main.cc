// ============================
// file: learn_std_list.cc
// 说明：全面学习 std::list 的现代 C++ 用法
// 编译：g++ -std=c++17 learn_std_list.cc -o learn_list
// ============================

#include <algorithm> // find, remove_if, sort (list 有专属 sort), unique
#include <iterator> // std::distance, std::ostream_iterator
#include <list>
#include <numeric> // accumulate
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
    bool operator==(const Node& other) const { return id == other.id; } // C++20 可省略
};

// 示例 1: 初始化方式
void example_init()
{
    std::println("\n=== 示例 1: 初始化方式 ===");

    // ✅ 默认构造
    std::list<int> lst1;
    std::println("lst1.size() = {}", lst1.size());

    // ✅ 初始化列表
    std::list<int> lst2 { 1, 2, 3, 4, 5 };
    print_container(lst2, "lst2");

    // ✅ 指定大小 + 默认值
    std::list<double> lst3(3, 3.14);
    print_container(lst3, "lst3");

    // ✅ 指定大小（值初始化）
    std::list<int> lst4(4);
    print_container(lst4, "lst4");

    // ✅ 拷贝构造
    std::list<int> lst5 = lst2;
    print_container(lst5, "lst5 (copy)");

    // ✅ 从迭代器范围构造
    std::list<int> lst6(lst2.begin(), --lst2.end()); // 除最后一个
    print_container(lst6, "lst6 (range)");
}

// 示例 2: 前后端操作（类似 deque）
void example_front_back()
{
    std::println("\n=== 示例 2: 前后端操作 ===");

    std::list<int> lst;

    // ✅ push_back / pop_back
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);

    // ✅ push_front / pop_front
    lst.push_front(0);
    lst.push_front(-1);

    print_container(lst, "After push_front/back");

    // ✅ 访问两端
    std::println("front: {}, back: {}", lst.front(), lst.back());

    // ✅ pop_front / pop_back
    lst.pop_front();
    lst.pop_back();
    print_container(lst, "After pop_front/back");
}

// 示例 3: 任意位置插入/删除 —— list 的核心优势！
void example_insert_erase()
{
    std::println("\n=== 示例 3: 任意位置插入/删除（核心优势） ===");

    std::list<int> lst { 10, 20, 30, 40, 50 };
    print_container(lst, "原始");

    // ✅ 获取迭代器（比如指向30）
    auto it = lst.begin();
    std::advance(it, 2); // 移动到索引2（30）

    // ✅ insert —— 在 it 位置前插入
    it = lst.insert(it, 99); // 插入99，返回指向99的迭代器
    print_container(lst, "insert 99 before 30");

    // ✅ erase —— 删除 it 指向的元素（99）
    it = lst.erase(it); // 删除99，返回指向下一个（30）的迭代器
    print_container(lst, "erase 99");

    // ✅ insert 多个元素
    lst.insert(it, 3, 88); // 在 it（30）前插入3个88
    print_container(lst, "insert 3x88 before 30");

    // ✅ insert 初始化列表
    lst.insert(lst.begin(), { 1, 2, 3 });
    print_container(lst, "insert {1,2,3} at begin");

    // ✅ clear
    lst.clear();
    std::println("clear 后 size = {}", lst.size());
}

// 示例 4: 迭代器与遍历（无随机访问！）
void example_iterators()
{
    std::println("\n=== 示例 4: 迭代器与遍历 ===");

    std::list<char> lst { 'A', 'B', 'C', 'D' };

    // ✅ 正向迭代
    std::println("Forward:");
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        std::print("{} ", *it);
    }
    std::println("");

    // ✅ 反向迭代
    std::println("Reverse:");
    for (auto it = lst.rbegin(); it != lst.rend(); ++it) {
        std::print("{} ", *it);
    }
    std::println("");

    // ✅ 范围 for
    std::println("Range-for:");
    for (const auto& c : lst) {
        std::print("{} ", c);
    }
    std::println("");

    // ❌ 不支持随机访问！
    // lst[2];        // 编译错误！
    // lst.at(2);     // 编译错误！

    // ✅ 如需“按索引访问”，必须用 std::advance
    auto it = lst.begin();
    std::advance(it, 2); // O(n) 时间！
    std::println("Element at 'index' 2: {}", *it);
}

// 示例 5: list 专属算法 —— sort, merge, unique, splice, remove
void example_list_algorithms()
{
    std::println("\n=== 示例 5: list 专属算法 ===");

    std::list<int> lst { 4, 1, 9, 0, 5, 0, 3, 0, 2, 8 };
    print_container(lst, "原始数据");

    // ✅ sort —— list 有成员函数 sort（比 std::sort 更高效，因利用链表结构）
    lst.sort();
    print_container(lst, "排序后（list::sort）");

    // ✅ unique —— 移除连续重复元素（必须先排序）
    lst.unique();
    print_container(lst, "去重后（list::unique）");

    // ✅ remove —— 移除所有等于某值的元素
    lst.remove(0); // 移除所有0
    print_container(lst, "移除所有0后（list::remove）");

    // ✅ remove_if —— 移除满足条件的元素
    lst.remove_if([](int x) { return x % 2 == 0; }); // 移除偶数
    print_container(lst, "移除偶数后（list::remove_if）");

    // ✅ merge —— 合并两个已排序的 list
    std::list<int> lst2 { 2, 4, 6, 8 };
    lst2.sort();
    lst.merge(lst2); // 合并 lst2 到 lst（lst2 变为空）
    print_container(lst, "合并 lst2 后");
    std::println("lst2.size() after merge: {}", lst2.size());

    // ✅ splice —— 剪切另一个 list 的元素到本 list（O(1)！）
    std::list<int> source { 100, 200, 300 };
    auto mid_it = source.begin();
    std::advance(mid_it, 1); // 指向200

    lst.splice(lst.begin(), source, mid_it); // 剪切 source 中的 200 到 lst 开头
    print_container(lst, "splice 200 to front");
    print_container(source, "source after splice (100,300 remain)");

    // ✅ reverse —— 反转整个 list
    lst.reverse();
    print_container(lst, "反转后");
}

// 示例 6: 与通用 STL 算法配合（注意：不支持随机访问）
void example_std_algorithms()
{
    std::println("\n=== 示例 6: 与 STL 算法配合 ===");

    std::list<int> lst { 1, 2, 3, 4, 5, 6, 7, 8 };

    // ✅ find —— 支持（输入迭代器足够）
    auto it = std::find(lst.begin(), lst.end(), 5);
    if (it != lst.end()) {
        std::println("找到 5");
    }

    // ✅ accumulate —— 支持
    int sum = std::accumulate(lst.begin(), lst.end(), 0);
    std::println("总和: {}", sum);

    // ❌ sort —— 不能用 std::sort！因为 list 迭代器不是随机访问迭代器
    // std::sort(lst.begin(), lst.end()); // 编译错误！

    // ✅ 但可以用 list::sort（见上例）

    // ✅ transform —— 支持（但需目标容器大小匹配）
    std::list<int> result;
    result.resize(lst.size()); // 必须先分配空间
    std::transform(lst.begin(), lst.end(), result.begin(), [](int x) { return x * x; });
    print_container(result, "平方后（transform）");

    // ✅ copy —— 支持
    std::list<int> copy_lst;
    std::copy(lst.begin(), lst.end(), std::back_inserter(copy_lst));
    print_container(copy_lst, "拷贝后（copy + back_inserter）");
}

// 示例 7: 移动语义与自定义类型
void example_move()
{
    std::println("\n=== 示例 7: 移动语义与自定义类型 ===");

    std::list<Node> nodes;

    // ✅ push_back —— 可能 move
    nodes.push_back(Node(1));

    // ✅ emplace_back —— 直接构造
    nodes.emplace_back(2);

    // ✅ push_front
    nodes.push_front(Node(3));
    nodes.emplace_front(4);

    // ✅ 插入中间（需要迭代器）
    auto it = nodes.begin();
    std::advance(it, 2); // 指向第3个元素
    nodes.emplace(it, 5); // 在 it 前插入

    std::println("nodes 大小: {}", nodes.size());

    // ✅ 析构自动调用
}

// 示例 8: 迭代器稳定性演示
void example_iterator_stability()
{
    std::println("\n=== 示例 8: 迭代器稳定性 ===");

    std::list<int> lst { 10, 20, 30, 40, 50 };

    // ✅ 获取指向 30 的迭代器
    auto it = lst.begin();
    std::advance(it, 2);
    std::println("it points to: {}", *it); // 30

    // ✅ 在开头插入元素
    lst.push_front(5);
    std::println("After push_front(5), it still points to: {}", *it); // 仍为30！

    // ✅ 在末尾插入
    lst.push_back(60);
    std::println("After push_back(60), it still points to: {}", *it); // 仍为30！

    // ✅ 删除其他元素
    lst.pop_front(); // 删除5
    lst.pop_back(); // 删除60
    std::println("After pop_front/back, it still points to: {}", *it); // 仍为30！

    // ❌ 但删除 it 自身会使 it 失效！
    it = lst.erase(it); // 删除30，返回指向下一个（40）的迭代器
    std::println("After erase(it), it points to: {}", *it); // 40
}

// 主函数
auto main(int argc, char* argv[]) -> int
{
    example_init();
    example_front_back();
    example_insert_erase();
    example_iterators();
    example_list_algorithms();
    example_std_algorithms();
    example_move();
    example_iterator_stability();

    std::println("\n✅ std::list 学习完成！");
    return 0;
}